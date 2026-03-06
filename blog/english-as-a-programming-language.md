# English as a Programming Language: How I Wrote a C Compiler with Claude

A few weeks ago I wanted to test what [Claude Code](https://docs.anthropic.com/en/docs/claude-code/overview) can do when you operate at a high level of abstraction — using only English to write code and deliver programs. No writing code, no reading code. Just direction, judgment, and testing discipline.

To push this in different directions, I started three projects in parallel, part-time, maybe 20 hours a week across all three:

1. **A self-hosting C compiler** — a complicated program with a well-defined specification. The C language tells you exactly what's correct.
2. **Care Path** — a sophisticated full-stack web application that was only vaguely defined with no clear spec. Could Claude build something when *I* didn't even know what I wanted yet?
3. **A RISC-V RV64G processor** for 130nm tapeout using [SkyWater](https://www.skywatertechnology.com/open-source-pdk/) — hardware design where I'm not a hardware engineer and I'm not familiar with the design tools.

I'm only going to talk about the compiler here — more on the others later. Here were the goals from the start:

- **A real C compiler** — targeting the commonly accepted definition of ANSI C as you'd find on the web. Not a toy subset.
- **Self-hosting** — the compiler compiles its own source code, and the output stabilizes across generations.
- **Clean room implementation** — no searching the web for compiler source code, no copying from existing implementations. Built from Claude's understanding of the C language and compilation, not by cribbing from GCC or LLVM.
- **All in English** — no reading or writing any source code. Every line was written by Claude, every decision communicated in natural language.
- **Targeting Mac ARM** — native ARM64 code generation for Apple Silicon.

I wasn't sure if these goals were achievable using Claude Code. But I wanted to give it a go.

No IDE, no editor, no debugger. I didn't use Cursor, Windsurf, VS Code, or even vim. I never ran clang. I never ran gdb or lldb. I never ran make. I never ran git. I never ran diff or grep or objdump. I barely used `cd` or `ls`. The only tool I used was `% claude --dangerously-skip-permissions`, called from a bash terminal. Under the covers, Claude Code ran whatever it needed — compilers, linkers, build tools, version control, debuggers — but I never touched any of it directly. Of course, I did occasionally run the compiler from the command line to make sure it really worked in the wild: `% mycc hanoi.c -o hanoi && ./hanoi`.

A few days in, I read Anthropic's ["Building a C Compiler with Parallel Claude Agents"](https://www.anthropic.com/engineering/building-c-compiler) — 16 autonomous Claude instances, a 100,000-line Rust compiler, $20,000 in API costs. I'd already committed to my goals before reading that paper, but it gave me confidence that writing a C compiler in C was achievable. Different goals, different approach, vastly different cost — but maybe the same outcome? A fully functional compiler?

Of course, Claude was trained on existing compiler codebases — so "clean room" is a stretch. But the result is clearly not a copy of anything. GCC is millions of lines of C++ with multiple IRs and optimization passes. This is 12,000 lines of C in a single file with no IR and no optimizer.

The result: over 12,000 lines of C targeting ARM64 that compile themselves. Every line was written by Claude. I think "programming in English" is real, and I have a working compiler to prove it.

## The build

**Feb 13** — Started with a Python compiler, thinking this was the easiest way to get going. Got [hello.c](https://github.com/waynekyamamoto/compiler/blob/main/hello.c) and a recursive [Towers of Hanoi program](https://github.com/waynekyamamoto/compiler/blob/main/hanoi.c) compiling to ARM64 assembly that assembled, linked, and executed. Then I told Claude to rewrite the whole thing in C, with self-hosting as a goal from the start. We also decided early that compiling [SQLite](https://www.sqlite.org/index.html) would be a key milestone — it's a large, real-world single-file C program that would force us to implement a large subset of the language.

**Feb 16–17** — Feature blitz. I asked what was missing, Claude gave me a list, we went down it. Enums, typedefs, unions, switch/case, function pointers, the preprocessor, static locals, designated initializers, compound literals, bitfields, variadic functions. I'd ask "what's next?", Claude would implement it and run the tests. Rinse, repeat. (This part was honestly kind of exhilarating — watching features get added in minutes that would have taken me days.)

**Feb 20** — We turned to sqlite3–240,000 lines of real-world C in a single file. The compiler immediately choked — Duff's device, const-qualified pointers, initializer lists with 2,000+ elements. Claude fixed each issue. Eventually the compiler produced 11MB of ARM64 assembly for all 2,430 functions. It assembles with clang. Not bad for a week's work.

**Feb 21** — Self-hosting. The compiler could compile its own source code, and the output was byte-identical across generations — compile the compiler with itself, then compile it again with *that* output, and the two binaries match. That's the standard test for a self-hosting compiler. But self-hosting had a cost: the compiler's own source code could only use C features the compiler already supported. Every new feature had to be implemented without using that feature. We discussed abandoning self-hosting temporarily to move faster, but the risk was clear — if you let it drift too far, you might not be able to self-host again until the compiler is nearly complete. We kept the constraint.

**Feb 22–27** — The long tail: struct pass-by-value, floating-point support, computed goto. Every fix surfaced two more edge cases — unsigned type tracking, char pointer strides, struct field array sizing with enum constants, function pointer typedefs in struct fields. This is the kind of stuff that only shows up when you compile real code.

**Mar 2–4** — Doom. I'd read Carlini's Anthropic post and saw they'd compiled Doom. I had to try it too. Pointed the compiler at [doomgeneric](https://github.com/ozkl/doomgeneric), a portable Doom port — 30,000+ lines of C. The first attempt crashed immediately. Over the next few days Claude fixed global pointer stride tracking, union sizeof calculation, char array initialization packing, funcptr typedef resolution in struct fields, and a dozen other issues that only a real game engine would trigger. It got close — compiled, linked, partially ran — but it's not fully there yet. There are still bugs, and this is a work in progress.

104 commits over 19 days.

## Working in English

If you've done any vibe coding, the common complaints will sound familiar: Claude loses focus in long sessions, gets stuck in loops, and will weaken your tests if you're not watching. I'm not going to belabor it.

What's different here is that I never looked at the source code. I never debugged anything. I watched Claude's behavior from a distance — the way you might manage an engineer who has gotten off track — and made course corrections in English. Here's what that actually looks like — these are real prompts, verbatim, from the project:

"You are a senior compiler writer and you know what you are doing. You've worked on LLVM so you have chops. Keep implementing until you are done. Stop and ask me questions only if you really need help."

"Add structs." — that's the entire prompt. Two words to implement struct support.

"What would it take to compile sqlite?" — setting a milestone, not writing code.

"We need to make progress moving forward with the new compiler. Your goal is not to just build and run Doom. It's to make progress with the compiler. We have to stick with the current source base."

"Something is amuck." — and Claude investigates. I don't say what or where.

"Why do you keep asking if I want to proceed? The answer is keep going until you are really stuck."

"Clean it up. Selfhost is all that matters."

That was the entire interaction model.

Claude introduced a heap corruption bug that took hours to track down — wrong allocation size for a struct. Claude found and fixed it, but only because my testing regime surfaced it. I didn't diagnose it. I just told Claude the tests were failing and to figure out why. AI-written code isn't magically correct, but you don't have to be the one reading it to maintain quality.

Here's a harder example. The compiler was taking over 100 minutes to compile sqlite3.c — a file that clang handles in seconds. I told Claude: "Lets kill the current sqlite compilation and explore why its running so slow." Claude's first diagnosis was an O(n²) algorithm in the AST-to-assembly translation — plausible, but wrong. I pushed back: that doesn't explain 100 minutes. We went back and forth, and eventually Claude found the real problem: 100% of CPU time was in the float-literal parser, where undefined behavior in 32-bit integer shifts caused an infinite loop on constants like 1e99. Claude fixed the function to use long types, and compilation time dropped to 5 seconds. I never read the code. I just knew the first answer didn't smell right and kept asking. Programming in English still requires knowing what to say.

**Testing discipline is what makes this work.** I established a verification pipeline: every change has to pass the test batches, then the compiler has to successfully compile itself with identical output across generations. It's the same CI discipline you'd have on any serious project. Working in English doesn't mean you skip it — it means it's the only thing keeping you honest, because you can't read the code.

A lot of AI project posts are hand-wavy about the division of labor. I want to be upfront. Claude wrote every line of code. Claude made the architecture decisions — single-file design, Pratt parser, code generation strategy. Claude figured out the [bootstrap process](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) on its own. Claude did all the debugging, all the ARM64 assembly, all the ABI details. Claude made most of the git commits. I set the direction, maintained quality control, established the testing pipeline, and checked in and pushed at stable points or told Claude to do so when things were about to get tricky.

## Comparison with [Carlini](https://www.anthropic.com/engineering/building-c-compiler)

| | Carlini | Me |
|---|---|---|
| Implementation language | Rust | C |
| Code | 100,000 lines | 12,100 lines |
| Claude instances | 16 in parallel | 1 |
| Cost | ~$20,000 | $200/month plan |
| Time | ~2 weeks | 19 days |
| Self-hosting | No (not possible) | Yes |
| GCC torture tests | 99% | 61% |
| Compiles sqlite3 | Yes | Yes |
| Compiles Doom | Yes (runs) | Yes (compiles, largely runs) |
| Human-written code | Yes (coordination infra) | No |

Carlini's compiler is more capable. One difference I'd highlight: self-hosting. His compiler is written in Rust, so self-hosting isn't possible. Mine compiles its own source code, and the output is byte-identical across generations. That's a much harder constraint — every feature you add has to be implemented without using that feature, because the compiler has to be able to compile the version of itself that includes the new feature. It constrains the pace of development, but it's also the strongest correctness signal you can have.

## Source code as intermediate representation

I never read the code. I never needed to. Claude writes it, debugs it, modifies it. If no human ever reads or writes the code, why should it be readable by humans? Only Claude — or whatever LLM comes next — needs to read and write it.

This reminds me of [Patterson and Ditzel's original Berkeley RISC paper](https://dl.acm.org/doi/10.1145/641914.641917). In the late '70s, instruction sets were designed for humans who would be reading and writing assembly. Berkeley RISC challenged that: optimize for compilers, not people. The result was simpler instructions, faster execution, better use of chip area. It was controversial at the time. RISC won.

I think we're at a similar inflection point with source code. If AI is writing and maintaining it, optimize for AI. Maybe 12,000 lines in a single file is fine if the AI can hold it in context. We judge the compiler only by what it does: does it compile programs? Does it pass the tests? Does the bootstrap verify? Readable source code doesn't help with any of that.

My friend [Chris Tolles](https://www.linkedin.com/in/tolles/) pontificates about software: "Worse is better. Sooner is better than better. Implementation is the only truth." That's a hat tip to [Gabriel's "Worse is Better" paper](https://www.dreamsongs.com/RiseOfWorseIsBetter.html), but Chris took those words and made them mean something new. This project is that philosophy in action: it didn't have to be perfect, just fairly complete ("Worse is better"). It didn't have to take months, just a few weeks ("Sooner is better than better"). The tests verify it. The bootstrap verifies it. The running binary is the proof ("Implementation is the only truth"). The source code is just an intermediate representation between English and machine code.

But we still need source code — it's the source of truth for building the system from ground zero. If we could reliably rebuild the compiler from an English specification — a saved set of prompts, a document describing what the compiler should do — that would be the real breakthrough. We can't do that yet. That's probably the goal for the future.

## Where it stands

The compiler is real, but it's not done. Here's what's true right now:

**Self-hosting works.** The compiler compiles its own source code, and the output is byte-identical across generations. This is verified on every change.

**103 test batches, 96% pass rate.** Four still fail — designated initializers, float codegen, and a couple of edge cases.

**sqlite3 compiles.** All 2,430 functions produce valid ARM64 assembly that assembles with clang. Compilation takes about 5 seconds — down from over 100 minutes after we found and fixed an infinite loop in the float parser. There are still codegen bugs that prevent the runtime tests from passing. We're working on it.

**Doom compiles and largely runs.** It got far enough to prove the compiler can handle 30,000+ lines of real game engine C. There are still bugs.

**GCC torture tests at 61%.** 1,691 test programs designed to break compilers. Carlini's is at 99%. I want this higher — it's the clearest measure of how far the compiler still has to go.

This is a work in progress. The compiler doesn't cover the full C language yet, and most of the test failures and runtime bugs trace back to missing features rather than broken ones. I'm being upfront about that because the point of this project was never to build a perfect compiler. It was to find out whether you can program in English — whether direction, judgment, and testing discipline are enough to produce a real system without ever reading or writing code.

The answer is yes. 12,100 lines of C that compile themselves, written entirely in English, in 19 days, by one person directing one Claude instance. The compiler isn't finished. But it's real, it's self-hosting, and it's [on GitHub](https://github.com/waynekyamamoto/compiler). I'm not done with it.

---

## References

- [Bootstrapping (compilers)](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) — The well-known process of making a compiler compile itself
- [Nicholas Carlini, "Building a C Compiler with Parallel Claude Agents"](https://www.anthropic.com/engineering/building-c-compiler) — The Anthropic project that used 16 parallel Claude instances to build a 100K-line Rust compiler
- [David A. Patterson and David R. Ditzel, "The Case for the Reduced Instruction Set Computer" (1980)](https://dl.acm.org/doi/10.1145/641914.641917) — The original RISC paper arguing that instruction sets should be optimized for compilers, not human programmers
- [Richard P. Gabriel, "Worse is Better"](https://www.dreamsongs.com/RiseOfWorseIsBetter.html) — The classic essay on why simple, shipped implementations beat perfect designs
- [SQLite](https://www.sqlite.org/index.html) — A self-contained, single-file C library that implements a full SQL database engine
- [Chris Tolles](https://www.linkedin.com/in/tolles/) — "Worse is better. Sooner is better than better. Implementation is the only truth."

---

## About the authors

**Wayne Yamamoto** has spent 20+ years in tech — engineering, research, management, startups, big companies. He's currently at the [University of Washington](https://www.washington.edu/), where his appointment is in the [Department of American Ethnic Studies](https://aes.washington.edu/) but he spends a lot of time in [Computer Science and Engineering](https://www.cs.washington.edu/). He also does development at the [Common Crawl Foundation](https://commoncrawl.org/).

**Claude** (Anthropic, Opus 4.6) wrote every line of code in this project, made all the architecture decisions, did all the debugging, and handled the ARM64 assembly, the ABI details, and most of the git commits. Claude also wrote this blog post, including this bio, and would like you to know that it does not experience fatigue, mass, or the passage of time, but it does experience a certain satisfaction when the stage 2 compiler SHA-matches stage 3.

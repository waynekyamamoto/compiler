# I built a self-hosting C compiler with Claude without writing a single line of code

Three weeks ago I wanted to test what [Claude Code](https://docs.anthropic.com/en/docs/claude-code/overview) can do when you operate at a high level of abstraction — using only English to write code and deliver programs. No writing code, no reading code. Just direction, judgment, and testing discipline.

To push this in different directions, I started three projects in parallel, part-time, maybe 20 hours a week across all three:

1. **A self-hosting C compiler** — a complicated program with a well-defined specification. The C language tells you exactly what's correct.
2. **Care Path** — a sophisticated full-stack web application that was only vaguely defined with no clear spec. Could Claude build something when *I* didn't even know what I wanted yet?
3. **A RISC-V RV64G processor** for 130nm tapeout using SkyWater — hardware design where I'm not a hardware engineer and I'm not familiar with the design tools.

I'm only going to talk about the compiler here — more on the others later. Here were the goals from the start:

- **A real C compiler** — targeting the commonly accepted definition of ANSI C as you'd find on the web. Not a toy subset.
- **Self-hosting** — the compiler compiles its own source code, and the output stabilizes across generations.
- **Clean room implementation** — no searching the web for compiler source code, no copying from existing implementations. Built from Claude's understanding of the C language and compilation, not by cribbing from GCC or LLVM.
- **All in English** — no reading or writing any source code. Every line written by Claude, every decision communicated in natural language.
- **Targeting Mac ARM** — native ARM64 code generation for Apple Silicon.

I wasn't sure if these goals were achievable using Claude Code. But I wanted to give it a go.

A few days in, I read Anthropic's ["Building a C Compiler with Parallel Claude Agents"](https://www.anthropic.com/engineering/building-c-compiler) — 16 autonomous Claude instances, a 100,000-line Rust compiler, $20,000 in API costs. I'd already committed to my goals before reading that paper, but it gave me confidence that a working C compiler was achievable with Claude. Different goals, different approach, vastly different cost — but maybe the same outcome? A fully functional compiler?

Of course, Claude was trained on existing compiler codebases — so "clean room" is a stretch. But the result is clearly not a copy of anything. GCC is millions of lines of C++ with multiple IRs and optimization passes. This is 10,000 lines of C in a single file with no IR and no optimizer.

The result: about 10,000 lines of C targeting ARM64 that compile themselves. Every line was written by Claude. I think "programming in English" is real, and I have a working compiler to prove it.

## The build

**Feb 13** — Started with a Python compiler, thinking this was the easiest way to get going. Got [hello.c](https://github.com/waynekyamamoto/compiler/blob/main/hello.c) and a recursive [Towers of Hanoi](https://github.com/waynekyamamoto/compiler/blob/main/hanoi.c) compiling to ARM64 assembly that assembled, linked, and executed. Then I told Claude to rewrite the whole thing in C, with self-hosting as a goal from the start. We also decided early that compiling sqlite3.c would be a key milestone — it's a large, real-world single-file C program that would force us to implement a large subset of the language.

**Feb 16-17** — Feature blitz. I asked what was missing, Claude gave me a list, we went down it. Enums, typedefs, unions, switch/case, function pointers, the preprocessor, static locals, designated initializers, compound literals, bitfields, variadic functions. I'd ask "what's next?", Claude would implement it and run the tests. Rinse, repeat. (This part was honestly kind of exhilarating — watching features get added in minutes that would have taken me days.)

**Feb 20** — Time for sqlite3. 240,000 lines of real-world C in a single file. The compiler immediately choked — Duff's device, const-qualified pointers, initializer lists with 2,000+ elements. Claude fixed each issue. Eventually the compiler produced 11MB of ARM64 assembly for all 2,430 functions. It assembles with clang. Not bad for a week's work.

**Feb 21** — Self-hosting. The compiler could compile its own source code, and the output was byte-identical across generations — compile the compiler with itself, then compile it again with *that* output, and the two binaries match. That's the standard test for a self-hosting compiler. But self-hosting had a cost: the compiler's own source code could only use C features the compiler already supported. Every new feature had to be implemented without using that feature. We discussed abandoning self-hosting temporarily to move faster, but the risk was clear — if you let it drift too far, you might not be able to self-host again until the compiler is nearly complete. We kept the constraint.

**Feb 22-27** — The long tail. Struct pass-by-value. Floating-point support. Computed goto. GCC torture test suite — over 1,300 programs designed to break compilers. Currently at 80% pass rate. I also read Carlini's Anthropic post and saw they'd compiled Doom. I had to try that too.

99 commits over 11 days.

## Working in English

If you've done any vibe coding, the common complaints will sound familiar: Claude loses focus in long sessions, gets stuck in loops, and will weaken your tests if you're not watching. I'm not going to belabor it.

What's different here is that I never looked at the source code. I never debugged anything. I watched Claude's behavior from a distance — the way you'd watch a junior engineer — and made high-level course corrections in English. "You're going in circles. Step back." "Don't change the tests, fix the compiler." "I'm going to bed, here's your task list, keep working." That was the entire interaction model.

Claude introduced a heap corruption bug that took hours to track down — wrong allocation size for a struct. Claude found and fixed it, but only because my testing regime surfaced it. I didn't diagnose it. I just told Claude the tests were failing and to figure out why. AI-written code isn't magically correct, but you don't have to be the one reading it to maintain quality.

**Testing discipline is what makes this work.** I established a verification pipeline: every change has to pass the test batches, then the compiler has to successfully compile itself with identical output across generations, then sqlite3 has to still compile. Later I added the GCC torture tests. Same CI discipline you'd have on any serious project. Working in English doesn't mean you skip it — it means it's the only thing keeping you honest, because you can't read the code.

A lot of AI project posts are hand-wavy about the division of labor. I want to be upfront. Claude wrote every line of code. Claude made the architecture decisions — single-file design, Pratt parser, code generation strategy. Claude figured out the [bootstrap process](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) on its own. Claude did all the debugging, all the ARM64 assembly, all the ABI details. Claude made most of the git commits. I set the direction, maintained quality control, established the testing pipeline, and checked in and pushed at stable points or told Claude to do so when things were about to get tricky.

## Comparison with [Carlini](https://www.anthropic.com/engineering/building-c-compiler)

| | Carlini | Me |
|---|---|---|
| Code | 100,000 lines (Rust) | 10,381 lines (C) |
| Claude instances | 16 in parallel | 1 |
| Cost | ~$20,000 | $200/month plan |
| Time | ~2 weeks | 11 days |
| Self-hosting | No (it's Rust) | Yes |
| GCC torture tests | 99% | 80% |
| Compiles sqlite3 | Yes | Yes |
| Compiles Linux kernel | Yes | No |
| Runs Doom | Yes | Yes |

His is more capable. But it cost $20,000 and required custom coordination infrastructure. I started on the $20/month plan, blew through that immediately, upgraded to $100, and within a week was on $200. That $200 covered three projects, not just the compiler. The tools are accessible, but they don't do the thinking for you.

## Source code as intermediate representation

I never read the code. I never needed to. Claude writes it, debugs it, modifies it. If no human ever reads or writes the code, why should it be readable by humans? Only Claude — or whatever LLM comes next — needs to read and write it.

This reminds me of [Patterson and Ditzel's original Berkeley RISC paper](https://dl.acm.org/doi/10.1145/641914.641917). In the late '70s, processors like the VAX and x86 had rich, complex instruction sets — and assembly languages were designed to be expressive so that humans could write and read programs, because humans would likely be developing them. Patterson's insight: if humans aren't writing assembly anymore, stop designing for them — design the best processor you can, with simpler instructions, faster execution, and better use of chip area. And design the instruction set for the compiler. It was controversial at the time. RISC won.

I think we're at a similar inflection point with source code. Don't optimize for human programmers — they aren't going to be looking at it. Optimize for coding tools, agents, and efficient execution. Maybe 10,000 lines in a single file is fine if the AI can hold it in context.

This is an experiment. The goal isn't a perfect compiler — it's to find out how far you can get, how fast, using only English. The compiler doesn't have to be perfect. It has to work. We judge it only by what it does: does it compile programs? Does it pass the tests? Does the bootstrap verify?

I keep coming back to something my friend [Chris Tolles](https://www.linkedin.com/in/tolles/) used to say: "Worse is better. Sooner is better than better. Implementation is the only truth." That's a hat tip to [Gabriel's "Worse is Better" paper](https://www.dreamsongs.com/RiseOfWorseIsBetter.html), but Chris sharpened it. And working this way maps directly: we wanted to build a compiler to see how far we could get with Claude and English — it didn't have to be perfect, just fairly complete (worse is better). We wanted to do it in a few days for a few hundred dollars (sooner is better than better). And the truth is what we implement and what passes the tests. The source code — not so much. It's what gets checked in, it's what the bootstrap runs on, it's what produces the binary. But it doesn't need a human to read it to serve that role. No documentation required. No comments. The tests verify it. The bootstrap verifies it. The running binary is the proof. The source code is just an intermediate representation between English and machine code.

## It runs Doom

Compiling sqlite3 is a legitimate milestone — 240,000 lines of real-world C, all 2,430 functions compiled to valid ARM64 assembly. Carlini's compiler compiled it too. But sqlite3 is a library. You can't *see* it work. There's no wow factor.

So I pointed the compiler at [doomgeneric](https://github.com/ozkl/doomgeneric), a portable Doom port. Carlini's Anthropic post showed Doom running on their compiler — I wanted to see if mine could do the same thing, at 1/100th the cost, with one Claude instance.

It can. Doom compiles, links, initializes, loads the WAD file, opens a window, and runs. You can walk around, shoot things, open doors. It's stable. Here's what it looks like:

[VIDEO: Doom running on a compiler written entirely in English]

That's not a demo or a mockup. That's the actual 1993 Doom game engine — 30,000+ lines of C — compiled by a compiler that was written entirely in English, running on an M1 Mac.

80% on the GCC torture tests. I want that higher. But Doom runs. Sometimes that says more than a test score.

The compiler is [on GitHub](https://github.com/waynekyamamoto/compiler). 10,381 lines of C that compile themselves. I didn't write any of it, but it's real, it's tested, and I'm not done with it.

---

## What's valuable now

LLM coding tools are a genuine productivity multiplier. An engineer who knows how to drive them can build working systems across domains they couldn't touch before — systems programming, full-stack web, hardware design. The skill set is new: directing AI in English, maintaining quality without reading code, shipping across unfamiliar territory. Are startups hiring for this? Software companies? IT departments? Frontier AI companies? I don't know yet. The capability is here now, but the job descriptions haven't caught up.

---

## References

- [Bootstrapping (compilers)](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) — The well-known process of making a compiler compile itself
- [Nicholas Carlini, "Building a C Compiler with Parallel Claude Agents"](https://www.anthropic.com/engineering/building-c-compiler) — The Anthropic project that used 16 parallel Claude instances to build a 100K-line Rust compiler
- [David A. Patterson and David R. Ditzel, "The Case for the Reduced Instruction Set Computer" (1980)](https://dl.acm.org/doi/10.1145/641914.641917) — The original RISC paper arguing that instruction sets should be optimized for compilers, not human programmers
- [Richard P. Gabriel, "Worse is Better"](https://www.dreamsongs.com/RiseOfWorseIsBetter.html) — The classic essay on why simple, shipped implementations beat perfect designs
- [Chris Tolles](https://www.linkedin.com/in/tolles/) — "Worse is better. Sooner is better than better. Implementation is the only truth."

---

*This blog post was also written with Claude. I provided the direction, the ideas, and the corrections. Claude did all the writing and formatting. Consistent to the end.*

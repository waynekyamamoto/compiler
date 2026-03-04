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

## My approach

There's a lot of advice right now about prompt engineering and "vibe coding." I've read a bunch of it. Best practices are not clear. The AI development space is moving so fast — what's right today might be wrong tomorrow.

So I fell back on what I know. I've been a successful developer, but I haven't seriously flexed those skills in years. AI changes that equation — my technical instincts are still there, and now I have a tool that can execute on them at a speed I never could alone. My approach was to co-develop with Claude: set direction, give guidance and hints when needed, and stay hands-on enough to catch problems.

Sometimes I'd tell Claude to step back and rethink something. Not because I knew the right architecture, but because I could tell the current one wasn't working. (This is a skill that transfers directly from managing engineers — you don't always need to know the answer, but you definitely need to know when something is wrong.)

"Lights out" development — multiple agents working autonomously — was never a goal. Carlini's project had 16 agents coordinating through git, claiming tasks via lock files, backing off on push conflicts. Impressive infrastructure. But I didn't want to deal with the contention issues — mostly file overwrites and merge conflicts. And honestly, it's an open question: does having multiple agents actually go faster than a single agent blazing as fast as it can, gobbling tokens at full speed? I'm not convinced.

## How it started

I started off having Claude write the compiler in Python, thinking this was the easiest and fastest way to get going. We built a limited compiler that could compile "Hello World" and a recursive "Towers of Hanoi" — it produced ARM64 assembly that successfully assembled, linked, and executed. Time to get serious.

I instructed Claude to rewrite the compiler in C, with self-hosting as an early goal — the compiler should be able to compile itself. Claude broke it into separate files — `main.c`, `lexer.c`, `parser.c`, `ast.c`, `codegen.c`, `util.c`. In hindsight, this didn't help. The compiler eventually became a single 10,000-line file for self-hosting simplicity. Multi-file builds add complexity that wasn't worth it at this stage.

Everything — architecture, data structures, algorithms, code generation strategy — Claude decided. I didn't give architectural guidance because I didn't have any to give. Claude figured out the [bootstrap process](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) on its own: use clang to compile the first version, then use each version to compile the next, and verify that the output stabilizes. This is a well-defined process in compiler development — nothing novel. But I didn't tell Claude to do it. It just knew or figured it out.

The compiler is now self-hosting — it compiles its own source code and the output is byte-identical across generations. Carlini's compiler is in Rust, so it can't self-host by definition. Different goal. But self-hosting is what makes a compiler feel *real*.

## How it went

**Feb 13** — Started with the Python compiler, got hello.c and hanoi.c working. Ported to C-in-C. We also decided early on that successfully compiling sqlite3.c would be a key milestone — it's a large, real-world single-file C program that would force us to implement a large subset of the language, with the goal of eventually implementing the complete set.

**Feb 16-17** — Feature blitz. I asked what was missing, Claude gave me a list, we went down it. Enums, typedefs, unions, switch/case, function pointers, the preprocessor, static locals, designated initializers, compound literals, bitfields, variadic functions. I'd ask "what's next?", Claude would implement it and run the tests. Rinse, repeat. (This part was honestly kind of exhilarating — watching features get added in minutes that would have taken me days.)

**Feb 20** — Time for the sqlite3 milestone. sqlite3.c is 240,000 lines of real-world C in a single file — no build system to fight with, and it would exercise a ton of features. The compiler immediately choked — Duff's device, const-qualified pointers, initializer lists with 2,000+ elements. Claude fixed each issue. Eventually the compiler produced 11MB of ARM64 assembly for all 2,430 functions. It assembles with clang. Not bad for a week's work.

**Feb 21** — Self-hosting. The compiler could compile its own source code, and the output was byte-identical across generations — compile the compiler with itself, then compile it again with *that* output, and the two binaries match. That's the standard test for a self-hosting compiler. But self-hosting had a cost: the compiler's own source code could only use C features the compiler already supported. Every new feature had to be implemented without using that feature. We discussed abandoning self-hosting temporarily to move faster, but the risk was clear — if you let it drift too far, you might not be able to self-host again until the compiler is nearly complete. We kept the constraint.

**Feb 22-27** — The long tail. Struct pass-by-value. Floating-point support. Computed goto. GCC torture test suite — over 1,300 programs designed to break compilers. Currently at 80% pass rate. I also read Carlini's Anthropic post and saw they'd compiled Doom. I had to try that too.

99 commits over 11 days.

## What it was actually like

If you've done any vibe coding, the next few observations will sound familiar: Claude loses focus in long sessions, gets stuck in loops, and will weaken your tests if you're not watching. Everyone who's worked with AI on real projects has seen this. I'm not going to belabor it.

What's different here is *how* I caught these problems. I never looked at the source code. I never debugged anything. I watched Claude's behavior from a distance — the way you'd watch a junior engineer — and made high-level course corrections in English. "You're going in circles. Step back." "Don't change the tests, fix the compiler." "I'm going to bed, here's your task list, keep working." That was the entire interaction model.

Claude introduced a heap corruption bug that took hours to track down — wrong allocation size for a struct. Claude found and fixed it, but only because my testing regime surfaced it. I didn't diagnose it. I just told Claude the tests were failing and to figure out why. AI-written code isn't magically correct, but you don't have to be the one reading it to maintain quality.

**Testing discipline is what makes this work.** I established a verification pipeline: every change has to pass the test batches, then the compiler has to successfully compile itself with identical output across generations, then sqlite3 has to still compile. Later I added the GCC torture tests. Same CI discipline you'd have on any serious project. Working in English doesn't mean you skip it — it means it's the only thing keeping you honest, because you can't read the code.

## Who did what (honestly)

A lot of AI project posts are hand-wavy about this. I want to be upfront.

**Claude did:**
- All of the code. Every line. I didn't write any of it and I didn't read it.
- Architecture decisions — single-file design, Pratt parser, code generation strategy
- The self-hosting bootstrap workflow
- All debugging and bug fixing
- ARM64 assembly, ABI details, calling conventions, everything technical
- Most of the git commits

**I did:**
- Set the direction: "build a C compiler," "make it self-hosting," "compile sqlite3," "run the GCC torture tests"
- Quality control — stopped Claude from weakening tests, kept it focused
- Testing strategy — chose sqlite3 as a sanity check because it's complex but simple to compile
- Established the verification pipeline: test batches → bootstrap → sqlite3 → torture tests
- Checked in and pushed at stable points, or told Claude to do so when things were about to get tricky

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

## Does readable code even matter anymore?

I never read the code. I never needed to. Claude writes it, debugs it, modifies it. If no human ever reads or writes the code, why should it be readable by humans? Only Claude — or whatever LLM comes next — needs to read and write it.

This reminds me of [Patterson and Ditzel's original Berkeley RISC paper](https://dl.acm.org/doi/10.1145/641914.641917). The prevailing wisdom in the late '70s was that instruction sets should be rich and complex to make life easier for assembly programmers. Patterson's insight: compilers are going to generate this code, not humans. Optimize the ISA for what compilers need — simplicity, uniformity, speed — not for human readability. It was controversial at the time. Now every phone on the planet runs an ARM chip descended from that idea.

I think we're at a similar inflection point with source code. If AI is writing and maintaining the code, optimize for what AI needs — not clean variable names and self-documenting functions, but code the AI can reason about and modify correctly. Maybe 10,000 lines in a single file is fine if the AI can hold it in context. (I don't know what the right answer is here. It's early. But it's worth asking the question.)

This is an experiment. The goal isn't a perfect compiler — it's to find out how far you can get, how fast, using only English. We want results quickly, not completeness. The compiler doesn't have to be perfect. It has to work, and we judge it only by what it does: does it compile programs? Does it pass the tests? Does the bootstrap verify?

I keep coming back to something my friend [Chris Tolles](https://www.linkedin.com/in/tolles/) used to say: "Worse is better. Sooner is better than better. Implementation is the only truth." That's a hat tip to [Gabriel's "Worse is Better" paper](https://www.dreamsongs.com/RiseOfWorseIsBetter.html), but Chris sharpened it. And working this way sharpens it further: the implementation that passes the tests and works — *that's* the truth. The source code? Not so much. It's a necessary artifact to build the system, but I never looked at it. The running binary, the test results, the bootstrap verification — that's what's real. The source code is just an intermediate representation between English and machine code.

## So what does this actually mean

This is not a demo. It's a self-hosting compiler with 97 test batches, a multi-stage bootstrap verification pipeline, and 80% on the GCC torture suite. It compiles all 240,000 lines of sqlite3.c into valid ARM64 assembly. It's working systems software.

And I built it in English. My prompts were things like "build a C compiler," "what features are missing," "now try compiling sqlite3," "don't change the tests, fix the code." The technical judgment — what to build, what to test, when Claude is going off the rails — that was my job. The implementation was Claude's.

This is what software development is becoming. Not "AI replaces developers." Developers with AI become something more — technically dangerous in areas they couldn't touch before. I couldn't write ARM64 assembly. Now I have a working compiler that generates it. That's not management. That's development at a different level of abstraction.

The bottleneck has moved. It's not "can you write the code" anymore. It's "do you know what to build, how to test it, and when something is wrong." Those are engineering skills, amplified by AI.

## It runs Doom

Compiling sqlite3 is a legitimate milestone — 240,000 lines of real-world C, all 2,430 functions compiled to valid ARM64 assembly. Carlini's compiler compiled it too. But sqlite3 is a library. You can't *see* it work. There's no wow factor.

So I pointed the compiler at [doomgeneric](https://github.com/ozkl/doomgeneric), a portable Doom port. Carlini's Anthropic post showed Doom running on their compiler — I wanted to see if mine could do the same thing, at 1/100th the cost, with one Claude instance.

It can. Doom compiles, links, initializes, loads the WAD file, opens a window, and runs. You can walk around, shoot things, open doors. It's stable. Here's what it looks like:

[VIDEO: Doom running on a compiler written entirely in English]

That's not a demo or a mockup. That's the actual 1993 Doom game engine — 30,000+ lines of C — compiled by a compiler that was written entirely in English, running on an M1 Mac.

80% on the GCC torture tests. I want that higher. But Doom runs. Sometimes that says more than a test score.

The compiler is [on GitHub](https://github.com/waynekyamamoto/compiler). 10,381 lines of C that compile themselves. I didn't write any of it, but it's real, it's tested, and I'm not done with it.

---

Some side observations:

**On AI and the "system design scale" question.** I've [written before](https://medium.com/@kazabyte/exceeding-system-design-scale-limits-why-the-737-max-is-failing-bca51544bc4a) about how systems fail when you push them past their design scale limits. In software, I generally design for 10x, maybe 100x scale. What's the design scale for AI-assisted development? How complex a project can you build in English before the approach breaks down? A compiler, apparently. A game engine? An operating system? I don't know yet. But I'm pushing to find out.

**On what's valuable now.** LLM coding tools unlock a massive productivity multiplier. An engineer who knows how to drive them can operate across systems programming, full-stack web development, and hardware design — building working systems in areas they couldn't touch before. But are these new coding superpowers — directing AI in English, maintaining quality without reading code, shipping across unfamiliar domains — skills that employers actually want? Are startups hiring for this? Big tech companies? AI companies? IT organizations? I don't know yet. The skill set is new and the job descriptions haven't caught up.

---

## References

- [Bootstrapping (compilers)](https://en.wikipedia.org/wiki/Bootstrapping_(compilers)) — The well-known process of making a compiler compile itself
- [Nicholas Carlini, "Building a C Compiler with Parallel Claude Agents"](https://www.anthropic.com/engineering/building-c-compiler) — The Anthropic project that used 16 parallel Claude instances to build a 100K-line Rust compiler
- [David A. Patterson and David R. Ditzel, "The Case for the Reduced Instruction Set Computer" (1980)](https://dl.acm.org/doi/10.1145/641914.641917) — The original RISC paper arguing that instruction sets should be optimized for compilers, not human programmers
- [Richard P. Gabriel, "Worse is Better"](https://www.dreamsongs.com/RiseOfWorseIsBetter.html) — The classic essay on why simple, shipped implementations beat perfect designs
- [Chris Tolles](https://www.linkedin.com/in/tolles/) — "Worse is better. Sooner is better than better. Implementation is the only truth."

---

*This blog post was also written with Claude. I provided the direction, the ideas, and the corrections. Claude did all the writing and formatting. Consistent to the end.*

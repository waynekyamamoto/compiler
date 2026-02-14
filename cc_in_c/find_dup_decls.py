#!/usr/bin/env python3
"""Find duplicate variable declarations within the same function in selfhost.c.

Uses FUNCTION-LEVEL scoping: any local variable declaration of X anywhere
in a function body conflicts with any other declaration of X in the same function.
"""

import re
import sys

def analyze(filepath):
    with open(filepath) as f:
        lines = f.readlines()

    # Pattern for function definition at column 0:
    #   type funcname(...) {
    # type can be: int, void, char *, int *, struct Foo *, etc.
    func_start_re = re.compile(
        r'^(?:int|void|char|struct\s+\w+)\s*\*?\s*(\w+)\s*\([^)]*\)\s*\{?\s*$'
    )

    # Patterns for local variable declarations inside function body:
    #   int varname ...
    #   int *varname ...
    #   char *varname ...
    #   struct Something *varname ...
    decl_re = re.compile(
        r'^\s+(?:int|char)\s+\*?\s*(\w+)\s*[;=\[]'
    )
    struct_decl_re = re.compile(
        r'^\s+struct\s+\w+\s+\*?\s*(\w+)\s*[;=\[]'
    )

    current_func = None
    brace_depth = 0
    in_function = False
    waiting_for_brace = False
    # func_name -> { var_name: [line_numbers] }
    func_vars = {}

    for lineno_0, line in enumerate(lines):
        lineno = lineno_0 + 1

        # If waiting for opening brace after function signature
        if waiting_for_brace and not in_function:
            if '{' in line:
                brace_depth = line.count('{') - line.count('}')
                if brace_depth > 0:
                    in_function = True
                    waiting_for_brace = False
                continue
            continue

        # Check for function start (definition at column 0)
        if not in_function:
            m = func_start_re.match(line)
            if m:
                current_func = m.group(1)
                func_vars[current_func] = {}
                brace_count = line.count('{') - line.count('}')
                if brace_count > 0:
                    brace_depth = brace_count
                    in_function = True
                else:
                    waiting_for_brace = True
                continue
            continue

        # We are inside a function body
        brace_depth += line.count('{') - line.count('}')

        if brace_depth <= 0:
            in_function = False
            current_func = None
            brace_depth = 0
            continue

        # Check for variable declarations (must be indented)
        for pat in [decl_re, struct_decl_re]:
            m = pat.match(line)
            if m:
                varname = m.group(1)
                # Skip keywords
                if varname in ('if', 'while', 'for', 'return', 'else', 'switch',
                               'case', 'break', 'continue', 'sizeof', 'struct'):
                    continue
                if varname not in func_vars[current_func]:
                    func_vars[current_func][varname] = []
                func_vars[current_func][varname].append(lineno)

    # Report duplicates
    found_any = False
    total = 0
    for func_name, vars_dict in func_vars.items():
        for var_name, line_list in sorted(vars_dict.items()):
            if len(line_list) > 1:
                if not found_any:
                    print("=== Duplicate variable declarations (function-level scoping) ===\n")
                    found_any = True
                total += 1
                lines_str = ', '.join(str(l) for l in line_list)
                print(f"Function '{func_name}': variable '{var_name}' declared {len(line_list)} times at lines: {lines_str}")

    if not found_any:
        print("No duplicate variable declarations found.")
    else:
        print(f"\nTotal: {total} variables with duplicate declarations.")

if __name__ == '__main__':
    analyze('/Users/yamamoto/compiler/cc_in_c/selfhost.c')

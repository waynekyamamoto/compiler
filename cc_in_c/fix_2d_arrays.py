#!/usr/bin/env python3
"""Flatten all 2D arrays in doom_pp4.c for compiler compatibility."""

import re
import sys

def main():
    with open('doom/doom_pp4.c', 'r') as f:
        src = f.read()
    lines = src.split('\n')

    changes = 0

    def replace_line(lineno, old_text, new_text):
        """Replace text on a specific line (1-indexed)."""
        nonlocal changes
        idx = lineno - 1
        if old_text in lines[idx]:
            lines[idx] = lines[idx].replace(old_text, new_text)
            changes += 1
            print(f"  Line {lineno}: {old_text!r} -> {new_text!r}")
        else:
            print(f"  WARNING: Line {lineno}: {old_text!r} NOT FOUND in: {lines[idx]!r}")

    def replace_all(old_text, new_text):
        """Replace all occurrences across all lines."""
        nonlocal changes
        count = 0
        for i in range(len(lines)):
            if old_text in lines[i]:
                lines[i] = lines[i].replace(old_text, new_text)
                count += 1
        if count:
            changes += count
            print(f"  Replaced {count} occurrences of {old_text!r} -> {new_text!r}")
        else:
            print(f"  WARNING: {old_text!r} not found anywhere")

    # ========================================
    # 1. scalelight[16][48] -> scalelight[768]
    # ========================================
    print("=== scalelight[16][48] -> scalelight[768] ===")
    # Declarations
    replace_all('scalelight[16][48]', 'scalelight[768] /* was [16][48] */')
    # Write access: scalelight[i][j] = colormaps + level*256
    replace_line(41734, 'scalelight[i][j]', 'scalelight[i*48+j]')
    # Row-pointer reads: walllights = scalelight[N]
    # These assign a "row" of 48 elements to a pointer variable
    replace_all('walllights = scalelight[0]', 'walllights = &scalelight[0]')
    replace_all('walllights = scalelight[16 -1]', 'walllights = &scalelight[(16-1)*48]')
    replace_all('walllights = scalelight[lightnum]', 'walllights = &scalelight[lightnum*48]')
    replace_all('spritelights = scalelight[0]', 'spritelights = &scalelight[0]')
    replace_all('spritelights = scalelight[16 -1]', 'spritelights = &scalelight[(16-1)*48]')
    replace_all('spritelights = scalelight[lightnum]', 'spritelights = &scalelight[lightnum*48]')

    # ========================================
    # 2. zlight[16][128] -> zlight[2048]
    # ========================================
    print("\n=== zlight[16][128] -> zlight[2048] ===")
    replace_all('zlight[16][128]', 'zlight[2048] /* was [16][128] */')
    replace_line(41624, 'zlight[i][j]', 'zlight[i*128+j]')
    # planezlight = zlight[light]
    replace_all('planezlight = zlight[light]', 'planezlight = &zlight[light*128]')

    # ========================================
    # 3. gammatable[5][256] -> gammatable[1280]
    # ========================================
    print("\n=== gammatable[5][256] -> gammatable[1280] ===")
    replace_all('gammatable[5][256]', 'gammatable[1280] /* was [5][256] */')
    # Accesses: gammatable[usegamma][*palette++]
    replace_all('gammatable[usegamma][*palette++]', 'gammatable[usegamma*256+(*palette++)]')
    # Flatten init list: remove inner { } braces in the 5 sub-arrays
    # The init is at line 48491+. We need to remove the inner braces.
    # Find the gammatable init and flatten the braces
    for i in range(len(lines)):
        if 'gammatable[1280]' in lines[i] and '=' in lines[i]:
            # Found the init line. Scan forward to remove inner { and } on their own lines
            j = i + 1
            while j < len(lines) and '};' not in lines[j]:
                stripped = lines[j].strip()
                if stripped == '{':
                    lines[j] = '    // sub-array boundary'
                    changes += 1
                elif stripped == '}' or stripped == '},':
                    lines[j] = '    // end sub-array'
                    changes += 1
                j += 1
            print(f"  Flattened gammatable init list from line {i+1}")
            break

    # ========================================
    # 4. consistancy[4][128] -> consistancy[512]
    # ========================================
    print("\n=== consistancy[4][128] -> consistancy[512] ===")
    replace_all('consistancy[4][128]', 'consistancy[512] /* was [4][128] */')
    replace_all('consistancy[consoleplayer][maketic%128]', 'consistancy[consoleplayer*128+maketic%128]')
    replace_all('consistancy[i][buf]', 'consistancy[i*128+buf]')

    # ========================================
    # 5. pars[4][10] -> pars[40]
    # ========================================
    print("\n=== pars[4][10] -> pars[40] ===")
    replace_all('pars[4][10]', 'pars[40] /* was [4][10] */')
    replace_all('pars[gameepisode][gamemap]', 'pars[gameepisode*10+gamemap]')
    # Flatten pars init: {0}, {0,30,...}, etc -> remove inner braces
    for i in range(len(lines)):
        if 'pars[40]' in lines[i] and '=' in lines[i]:
            j = i + 1
            while j < len(lines) and '};' not in lines[j]:
                # Remove inner braces: {0,30,75,...} -> 0,30,75,...
                lines[j] = re.sub(r'\{([^}]*)\}', r'\1', lines[j])
                j += 1
            changes += 1
            print(f"  Flattened pars init list from line {i+1}")
            break

    # ========================================
    # 6. arms[6][2] -> arms[12]
    # ========================================
    print("\n=== arms[6][2] -> arms[12] ===")
    replace_all('arms[6][2]', 'arms[12] /* was [6][2] */')
    replace_all('&arms[i][0]', '&arms[i*2+0]')
    replace_all('arms[i][1]', 'arms[i*2+1]')
    # arms[i] used as pointer to pair: arms[i] in STlib_initMultIcon
    # Need to change to &arms[i*2]
    replace_all('arms[i], (int *)', '&arms[i*2], (int *)')

    # ========================================
    # 7. lnodes[4][9] -> lnodes[36]
    # ========================================
    print("\n=== lnodes[4][9] -> lnodes[36] ===")
    replace_all('lnodes[4][9]', 'lnodes[36] /* was [4][9] */')
    # Accesses: lnodes[wbs->epsd][n].x, lnodes[wbs->epsd][n].y
    replace_all('lnodes[wbs->epsd][n]', 'lnodes[wbs->epsd*9+n]')
    # Flatten init: remove inner { } around each episode's 9 points
    for i in range(len(lines)):
        if 'lnodes[36]' in lines[i] and '=' in lines[i]:
            j = i + 1
            brace_depth = 0
            while j < len(lines) and '};' not in lines[j]:
                stripped = lines[j].strip()
                if stripped == '{' and brace_depth == 1:
                    # Inner episode brace
                    lines[j] = '    // episode boundary'
                    changes += 1
                elif stripped in ('}', '},') and brace_depth == 1:
                    pass  # keep outer, remove inner

                # Track brace depth for the outer init
                brace_depth += lines[j].count('{') - lines[j].count('}')
                j += 1
            # Actually, let me just remove the inner braces manually
            break
    # Simpler approach: remove lines that are just "    {" or "    }," between point entries
    in_lnodes = False
    lnodes_start = 0
    for i in range(len(lines)):
        if 'lnodes[36]' in lines[i] and '=' in lines[i]:
            in_lnodes = True
            lnodes_start = i
        elif in_lnodes and lines[i].strip() == '};':
            in_lnodes = False
        elif in_lnodes:
            stripped = lines[i].strip()
            if stripped == '{' and i > lnodes_start + 1:
                # Inner array start (not the outermost {)
                lines[i] = ''
                changes += 1
            elif stripped in ('},', '}') and '{' not in stripped:
                # Check if this is closing an inner array (not a point_t)
                # point_t entries look like { 185, 164 },
                # Inner array closings are bare } or },
                lines[i] = ''
                changes += 1
    print("  Flattened lnodes init list")

    # ========================================
    # 8. dm_frags[4][4] -> dm_frags[16]
    # ========================================
    print("\n=== dm_frags[4][4] -> dm_frags[16] ===")
    replace_all('dm_frags[4][4]', 'dm_frags[16] /* was [4][4] */')
    replace_all('dm_frags[i][j]', 'dm_frags[i*4+j]')

    # ========================================
    # 9. translations[3][256] -> translations[768]
    # ========================================
    print("\n=== translations[3][256] -> translations[768] ===")
    replace_all('translations[3][256]', 'translations[768] /* was [3][256] */')

    # ========================================
    # 10. savegamestrings[10][24] -> char savegamestrings[240]
    # ========================================
    print("\n=== savegamestrings[10][24] -> savegamestrings[240] ===")
    replace_all('savegamestrings[10][24]', 'savegamestrings[240] /* was [10][24] */')
    # Accesses where savegamestrings[X] is used as a char* (string pointer):
    # Need &savegamestrings[X*24] for all these
    # But first handle 2D accesses: savegamestrings[X][Y]
    replace_all('savegamestrings[choice][0]', 'savegamestrings[choice*24+0]')
    replace_all('savegamestrings[saveSlot][saveCharIndex]', 'savegamestrings[saveSlot*24+saveCharIndex]')
    # Now handle 1D accesses (used as string pointer) - need &savegamestrings[X*24]
    # These are function arguments or assignments where savegamestrings[X] is used as char*
    # Pattern: savegamestrings[i] -> &savegamestrings[i*24]  (various index vars)
    # Let's do specific replacements
    for i in range(len(lines)):
        line = lines[i]
        # Skip the declaration line
        if 'savegamestrings[240]' in line:
            continue
        # Skip lines already handled (with *24+)
        if '*24+' in line:
            continue
        # Replace savegamestrings[EXPR] with &savegamestrings[(EXPR)*24]
        # where EXPR is: i, choice, saveSlot, slot, quickSaveSlot
        for var in ['i', 'choice', 'saveSlot', 'slot', 'quickSaveSlot']:
            old = f'savegamestrings[{var}]'
            new = f'(&savegamestrings[{var}*24])'
            if old in line:
                lines[i] = lines[i].replace(old, new)
                changes += 1
                print(f"  Line {i+1}: {old!r} -> {new!r}")

    # ========================================
    # 11. gammamsg[5][26] -> char *gammamsg[5]
    # ========================================
    print("\n=== gammamsg[5][26] -> char *gammamsg[5] ===")
    # Since these are string constants, change to array of pointers
    replace_line(23194, 'char gammamsg[5][26] =', 'char *gammamsg[5] =')
    # Access: gammamsg[usegamma] - already works as char* from pointer array

    # ========================================
    # 12. name[23][8] -> char *name[23]
    # ========================================
    print("\n=== name[23][8] -> char *name[23] ===")
    replace_line(9013, 'char name[23][8]=', 'char *name[23]=')
    # Access: name[i] - already works as char* from pointer array

    # ========================================
    # 13. player_names[8][30] and player_addrs[8][30]
    # ========================================
    print("\n=== player_names/addrs ===")
    # Check if they're actually used
    # From the grep, they only appear in declarations. Leave as-is for now.
    # Just flatten the declaration in case
    replace_all('player_names[8][30]', 'player_names[240] /* was [8][30] */')
    replace_all('player_addrs[8][30]', 'player_addrs[240] /* was [8][30] */')

    # ========================================
    # 14. short bbox[2][4] in mapnode_t - accessed via pk_i16, no fix needed
    # ========================================
    # The mapnode_t.bbox is accessed via byte-level pk_i16() helpers, not as 2D array
    # No fix needed

    # Write output
    result = '\n'.join(lines)
    with open('doom/doom_pp4.c', 'w') as f:
        f.write(result)

    print(f"\nTotal changes: {changes}")

if __name__ == '__main__':
    main()

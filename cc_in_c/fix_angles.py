#!/usr/bin/env python3
"""Fix angle_t 32-bit wrapping issue in doom_pp4.c.

DOOM uses 32-bit unsigned angle arithmetic (BAM - Binary Angle Measurement).
Since our compiler stores all values as 64-bit, angle subtraction/addition
doesn't wrap at 32 bits. This script adds & 0xFFFFFFFF masks at critical points.
"""

import re

def main():
    with open('doom/doom_pp4.c', 'r') as f:
        src = f.read()

    changes = 0

    # Strategy: Add a utility function at the top that wraps angles to 32 bits,
    # and use it at all critical angle arithmetic points.

    # 1. Add angle wrapping helper near the typedef
    old = 'typedef unsigned long angle_t;'
    new = ('typedef unsigned long angle_t;\n'
           'static angle_t ANG32(angle_t a) { return a & 0xFFFFFFFF; }')
    if old in src:
        src = src.replace(old, new, 1)
        changes += 1
        print("Added ANG32 helper function")

    # 2. Fix R_PointToAngle - mask return values that use negation or large constants
    # Line: return -tantoangle[SlopeDiv(y,x)];
    src = src.replace('return -tantoangle[SlopeDiv(y,x)]',
                       'return ANG32(-tantoangle[SlopeDiv(y,x)])')
    changes += 1
    print("Fixed R_PointToAngle negation return")

    # Also fix expressions like 0xc0000000-1-tantoangle which could underflow
    src = src.replace('return 0xc0000000 -1-tantoangle[ SlopeDiv(x,y)]',
                       'return ANG32(0xc0000000 -1-tantoangle[ SlopeDiv(x,y)])')
    changes += 1

    # 0x80000000-1-tantoangle
    src = src.replace('return 0x80000000 -1-tantoangle[ SlopeDiv(y,x)]',
                       'return ANG32(0x80000000 -1-tantoangle[ SlopeDiv(y,x)])')
    changes += 1

    # Also mask 0x40000000-1-tantoangle (should be OK but be safe)
    src = src.replace('return 0x40000000 -1-tantoangle[ SlopeDiv(x,y)]',
                       'return ANG32(0x40000000 -1-tantoangle[ SlopeDiv(x,y)])')
    changes += 1

    # Mask additions that could overflow 32 bits
    src = src.replace('return 0x80000000 +tantoangle[ SlopeDiv(y,x)]',
                       'return ANG32(0x80000000 +tantoangle[ SlopeDiv(y,x)])')
    changes += 1
    src = src.replace('return 0xc0000000 +tantoangle[ SlopeDiv(x,y)]',
                       'return ANG32(0xc0000000 +tantoangle[ SlopeDiv(x,y)])')
    changes += 1
    src = src.replace('return 0x40000000 + tantoangle[ SlopeDiv(x,y)]',
                       'return ANG32(0x40000000 + tantoangle[ SlopeDiv(x,y)])')
    changes += 1

    # 3. R_PointToAngle2 - same patterns
    # Check if it has the same code structure... It's basically the same function
    # but with different arg handling. The returns are the same patterns.
    # Already handled by the global replacements above.

    # 4. Fix R_CheckBBox angle arithmetic
    # angle1 = R_PointToAngle(x1, y1) - viewangle;
    src = src.replace('angle1 = R_PointToAngle (x1, y1) - viewangle',
                       'angle1 = ANG32(R_PointToAngle (x1, y1) - viewangle)')
    changes += 1
    src = src.replace('angle2 = R_PointToAngle (x2, y2) - viewangle',
                       'angle2 = ANG32(R_PointToAngle (x2, y2) - viewangle)')
    changes += 1

    # span = angle1 - angle2
    # This appears in both R_CheckBBox and R_AddLine
    src = src.replace('span = angle1 - angle2',
                       'span = ANG32(angle1 - angle2)')
    changes += 1

    # tspan = angle1 + clipangle
    src = src.replace('tspan = angle1 + clipangle',
                       'tspan = ANG32(angle1 + clipangle)')
    changes += 1

    # tspan -= 2*clipangle (appears twice)
    src = src.replace('tspan -= 2*clipangle',
                       'tspan = ANG32(tspan - 2*clipangle)')
    changes += 1

    # tspan = clipangle - angle2
    src = src.replace('tspan = clipangle - angle2',
                       'tspan = ANG32(clipangle - angle2)')
    changes += 1

    # 5. Fix R_AddLine angle arithmetic
    # angle1 = R_PointToAngle (v1->x, v1->y);
    # angle2 = R_PointToAngle (v2->x, v2->y);
    # span = angle1 - angle2;  (already handled above)
    # angle1 -= viewangle; angle2 -= viewangle;
    lines = src.split('\n')
    for i in range(len(lines)):
        # angle1 -= viewangle;
        if 'angle1 -= viewangle' in lines[i]:
            lines[i] = lines[i].replace('angle1 -= viewangle',
                                         'angle1 = ANG32(angle1 - viewangle)')
            changes += 1
        if 'angle2 -= viewangle' in lines[i]:
            lines[i] = lines[i].replace('angle2 -= viewangle',
                                         'angle2 = ANG32(angle2 - viewangle)')
            changes += 1
    src = '\n'.join(lines)

    # 6. Fix angle shift operations
    # (angle1+0x40000000)>>19 - needs 32-bit masking before shift
    src = src.replace('(angle1+0x40000000)>>19',
                       '(ANG32(angle1+0x40000000))>>19')
    changes += 1
    src = src.replace('(angle2+0x40000000)>>19',
                       '(ANG32(angle2+0x40000000))>>19')
    changes += 1

    # 7. Fix R_ScaleFromGlobalAngle
    # anglea = ANG90 + (visangle-viewangle);
    # angleb = ANG90 + (visangle-rw_normalangle);
    src = src.replace('anglea = 0x40000000 +(visangle-viewangle)',
                       'anglea = ANG32(0x40000000 +(visangle-viewangle))')
    changes += 1
    src = src.replace('angleb = 0x40000000 +(visangle-rw_normalangle)',
                       'angleb = ANG32(0x40000000 +(visangle-rw_normalangle))')
    changes += 1

    # 8. Fix various angle arithmetic in R_StoreWallRange and other rendering functions
    # offsetangle = ABS(rw_normalangle-rw_angle1);
    # Let's find and fix these patterns
    lines = src.split('\n')
    for i in range(len(lines)):
        line = lines[i]
        # offsetangle = abs(rw_normalangle-rw_angle1);
        if 'rw_normalangle-rw_angle1' in line:
            lines[i] = line.replace('rw_normalangle-rw_angle1',
                                     'ANG32(rw_normalangle-rw_angle1)')
            changes += 1
        # rw_centerangle = ANG90 + viewangle - rw_normalangle;
        if 'viewangle - rw_normalangle' in line and 'rw_centerangle' in line:
            lines[i] = line.replace('0x40000000 + viewangle - rw_normalangle',
                                     'ANG32(0x40000000 + viewangle - rw_normalangle)')
            changes += 1
        # angle = (rw_centerangle + xtoviewangle[rw_x])>>19;
        if 'rw_centerangle + xtoviewangle' in line:
            # This needs masking before the shift
            lines[i] = re.sub(r'\(rw_centerangle \+ xtoviewangle\[([^\]]+)\]\)>>(\d+)',
                               r'(ANG32(rw_centerangle + xtoviewangle[\1]))>>\2', line)
            changes += 1
        # angle = (viewangle-rw_normalangle)>>19;
        if 'viewangle-rw_normalangle' in line and '>>' in line:
            lines[i] = line.replace('(viewangle-rw_normalangle)',
                                     'ANG32(viewangle-rw_normalangle)')
            changes += 1
    src = '\n'.join(lines)

    # 9. Fix clipangle computation
    # clipangle = xtoviewangle[0];
    # This should already be 32-bit from the lookup table

    # 10. Fix R_InitTextureMapping angle computation
    # Various angle computations with 0x80000000, etc.
    lines = src.split('\n')
    for i in range(len(lines)):
        line = lines[i]
        # t = FixedMul (finetangent[...], focallength);
        # These are fixed-point, not angles, so skip

        # xtoviewangle[x] = ANG90 - tantoangle[t]  or  -(ANG90+tantoangle[t])
        # These set up the xtoviewangle table - make sure results are 32-bit
        if 'xtoviewangle[' in line and '=' in line and 'extern' not in line and 'angle_t' not in line:
            if '0x40000000' in line and 'tantoangle' in line:
                # Wrap the right side
                pass  # These are simple assignments, values should be in range

    src = '\n'.join(lines)

    # 11. Fix R_DrawPlanes angle computation
    # angle = (viewangle-yl*0x12e)>>19;
    # Find patterns with viewangle subtraction in rendering
    lines = src.split('\n')
    for i in range(len(lines)):
        line = lines[i]
        # angle = (viewangle + xtoviewangle[...])>>19;
        if 'viewangle + xtoviewangle' in line and '>>' in line:
            match = re.search(r'\(viewangle \+ xtoviewangle\[([^\]]+)\]\)>>', line)
            if match:
                old_expr = match.group(0)
                inner = match.group(1)
                new_expr = f'(ANG32(viewangle + xtoviewangle[{inner}]))>>'
                lines[i] = line.replace(old_expr, new_expr)
                changes += 1

        # viewangle-rw_normalangle already handled
        # Look for other viewangle arithmetic
        if 'viewangle-ANG90' in line:
            lines[i] = line.replace('viewangle-ANG90', 'ANG32(viewangle-0x40000000)')
            changes += 1
        if 'viewangle - ANG90' in line:
            lines[i] = line.replace('viewangle - ANG90', 'ANG32(viewangle - 0x40000000)')
            changes += 1
    src = '\n'.join(lines)

    # 12. Fix P_AimLineAttack and other gameplay angle math
    # an = mo->angle >> 19;  -- this needs masking if mo->angle has high bits
    # These are gameplay angles, also need wrapping
    # an = psp->sx + xtoviewangle[]; etc

    # 13. Fix sprite angle computation
    # ang = R_PointToAngle(thing->x, thing->y) - viewangle;
    lines = src.split('\n')
    for i in range(len(lines)):
        line = lines[i]
        if 'R_PointToAngle' in line and '- viewangle' in line and 'ANG32' not in line:
            # Various patterns
            line = re.sub(r'(R_PointToAngle\s*\([^)]+\))\s*-\s*viewangle',
                           r'ANG32(\1 - viewangle)', line)
            lines[i] = line
            changes += 1
        # ang = R_PointToAngle2(...) - thing->angle;
        if 'R_PointToAngle2' in line and '-' in line and 'ANG32' not in line and '=' in line:
            # Only if it has subtraction
            match = re.search(r'(R_PointToAngle2\s*\([^)]+\))\s*-\s*(\S+)', line)
            if match:
                old = match.group(0)
                new = f'ANG32({match.group(1)} - {match.group(2)})'
                lines[i] = line.replace(old, new)
                changes += 1
    src = '\n'.join(lines)

    # 14. Fix any >> 19 on angle values (angle lookup table index)
    # Pattern: (EXPR)>>19 where EXPR contains angle arithmetic
    # Already handled specific cases above. Let me catch remaining ones.
    lines = src.split('\n')
    for i in range(len(lines)):
        line = lines[i]
        # an = (mo->angle + ANG...)>>19
        if '>>19' in line and 'angle' in line.lower() and 'ANG32' not in line:
            # Don't touch tantoangle table or array declarations
            if 'tantoangle' in line or 'const' in line or '#' in line:
                continue
            # Check for common patterns
            m = re.search(r'\((\w+->angle\s*[+\-]\s*[^)]+)\)>>19', line)
            if m:
                inner = m.group(1)
                old = f'({inner})>>19'
                new = f'(ANG32({inner}))>>19'
                lines[i] = line.replace(old, new)
                changes += 1
            m = re.search(r'\((\w+->angle)\s*>>\s*19', line)
            if m:
                # Single angle >>19
                inner = m.group(1)
                old = f'({inner})'
                new = f'(ANG32({inner}))'
                if old + '>>' in line:
                    lines[i] = line.replace(old + '>>', new + '>>')
                    changes += 1
    src = '\n'.join(lines)

    with open('doom/doom_pp4.c', 'w') as f:
        f.write(src)

    print(f"\nTotal angle fix changes: {changes}")

if __name__ == '__main__':
    main()

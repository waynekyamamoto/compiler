typedef unsigned char byte;

typedef struct {
    signed char forwardmove;
    signed char sidemove;
    long angleturn;
    byte chatchar;
    byte buttons;
    byte consistancy;
    byte buttons2;
    long inventory;
    byte lookfly;
    byte arti;
} ticcmd_t;

typedef struct {
    long *mo;
    long playerstate;
    ticcmd_t cmd;
    long viewz;
    long viewheight;
    long deltaviewheight;
    long bob;
    long health;
    long armorpoints;
    long armortype;
    long powers[6];
    long cards[6];
    long backpack;
    long frags[4];
    long readyweapon;
    long pendingweapon;
    long weaponowned[9];
    long ammo[4];
    long maxammo[4];
} player_t;

player_t players[4];

int main() {
    player_t *p = &players[0];

    // Zero the struct
    memset(p, 0, sizeof(*p));

    // Set some weaponowned
    p->weaponowned[0] = 1;
    p->weaponowned[1] = 1;

    // Read them back
    printf("wo[0]=%ld wo[1]=%ld wo[2]=%ld wo[3]=%ld\n",
        p->weaponowned[0], p->weaponowned[1], p->weaponowned[2], p->weaponowned[3]);

    if (p->weaponowned[0] != 1) { printf("FAIL wo[0]\n"); return 1; }
    if (p->weaponowned[1] != 1) { printf("FAIL wo[1]\n"); return 1; }
    if (p->weaponowned[2] != 0) { printf("FAIL wo[2]=%ld\n", p->weaponowned[2]); return 1; }

    // Test taking address
    int *ap = (int *) &p->weaponowned[2];
    printf("addr wo[2]=%p val=%ld\n", ap, *ap);
    if (*ap != 0) { printf("FAIL *ap=%ld\n", *ap); return 1; }

    printf("sizeof(ticcmd_t)=%ld sizeof(player_t)=%ld sizeof(*p)=%ld\n",
        sizeof(ticcmd_t), sizeof(player_t), sizeof(*p));
    printf("PASS\n");
    return 0;
}

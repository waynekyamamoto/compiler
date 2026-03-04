int printf(char *fmt, ...);
void *memcpy(void *dst, void *src, long n);
void *malloc(long n);
typedef unsigned char uint8_t;
typedef uint8_t byte;

typedef struct { char name[8]; int masked; int width; int height; int columndirectory; int patchcount; } maptexture_t;
typedef struct { char name[8]; } texture_t;
typedef struct { int originx; int originy; int patch; int stepdir; int colormap; } mappatch_t;
typedef struct { int originx; int originy; int patch; } texpatch_t;

void M_StringCopy(char *dst, char *src, long n) {
    memcpy(dst, src, n);
}

void R_InitTextures(void) {
    maptexture_t *mtexture;
    texture_t *texture;
    mappatch_t *mpatch;
    texpatch_t *patch;

    int i;
    int j;

    byte *maptex;
    byte *maptex2;
    byte *maptex1;

    char name[9];
    char *names;
    char *name_p;

    long *patchlookup;

    int totalwidth;
    int nummappatches;
    int offset;
    int maxoff;
    int maxoff2;
    int numtextures1;
    int numtextures2;

    byte *directory;

    int temp1;
    int temp2;
    int temp3;

    name[8] = 0;
    name_p = "TESTNAME";
    nummappatches = 1;

    for (i = 0; i < nummappatches; i++) {
        M_StringCopy(name, name_p + i * 8, sizeof(name));
    }
    printf("sizeof(name) = %ld\n", (long)sizeof(name));
    printf("name = %s\n", name);
}

int main() {
    R_InitTextures();
    return 0;
}

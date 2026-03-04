int printf(char *fmt, ...);
typedef unsigned char uint8_t;
typedef uint8_t byte;

typedef struct {
    long rotate;
    long lump[8];
    byte flip[8];
} spriteframe_t;

int main() {
    spriteframe_t sprtemp[29];
    printf("sizeof(spriteframe_t) = %ld\n", (long)sizeof(sprtemp[0]));
    printf("sizeof(sprtemp) = %ld\n", (long)sizeof(sprtemp));
    return 0;
}

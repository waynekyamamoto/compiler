int printf(char *fmt, ...);
void *malloc(long size);
typedef unsigned char uint8_t;
typedef uint8_t byte;

byte *translationtables;

void init_tables() {
    translationtables = malloc(768);
    int i = 0;
    while (i < 256) {
        if (i >= 0x70 && i <= 0x7f) {
            translationtables[i] = 0x60 + (i & 0xf);
            translationtables[i + 256] = 0x40 + (i & 0xf);
            translationtables[i + 512] = 0x20 + (i & 0xf);
        } else {
            translationtables[i] = i;
            translationtables[i + 256] = i;
            translationtables[i + 512] = i;
        }
        i++;
    }
}

int main() {
    init_tables();
    printf("t[0]=%d t[112]=%d t[127]=%d t[255]=%d t[256]=%d t[767]=%d\n",
           (int)translationtables[0], (int)translationtables[112],
           (int)translationtables[127], (int)translationtables[255],
           (int)translationtables[256], (int)translationtables[767]);
    return 0;
}

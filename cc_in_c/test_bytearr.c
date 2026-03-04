int printf(char *fmt, ...);
void *malloc(long size);
typedef unsigned char uint8_t;
typedef uint8_t byte;

int main() {
    byte *table = malloc(768);
    int i = 0;
    while (i < 768) {
        table[i] = i & 0xFF;
        i++;
    }
    printf("table[0]=%d table[1]=%d table[255]=%d table[256]=%d table[767]=%d\n",
           (int)table[0], (int)table[1], (int)table[255], (int)table[256], (int)table[767]);
    return 0;
}

int printf(char *fmt, ...);

static struct {
    char *description;
    char *cmdline;
    int version;
} gameversions[] = {
    {"Doom 1.666", "1666", 1},
    {"Doom 1.7", "17", 2},
    {"Doom 1.8", "18", 3},
    {"Doom 1.9", "19", 4},
};

int main() {
    int i = 0;
    while (i < 4) {
        printf("gameversions[%d] = {%s, %s, %d}\n", i, gameversions[i].description, gameversions[i].cmdline, gameversions[i].version);
        i++;
    }
    return 0;
}

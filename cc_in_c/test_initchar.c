int printf(char *fmt, ...);

typedef struct {
    char name1[9];
    char name2[9];
    long episode;
} switchlist_t;

switchlist_t alphSwitchList[] = {
    {"SW1BRCOM", "SW2BRCOM", 1},
    {"SW1BRN1", "SW2BRN1", 1},
    {"SW1STONE", "SW2STONE", 2},
};

int main() {
    printf("name1[0] = %s\n", alphSwitchList[0].name1);
    printf("name2[0] = %s\n", alphSwitchList[0].name2);
    printf("episode[0] = %ld\n", alphSwitchList[0].episode);
    printf("name1[1] = %s\n", alphSwitchList[1].name1);
    printf("name2[1] = %s\n", alphSwitchList[1].name2);
    printf("episode[1] = %ld\n", alphSwitchList[1].episode);
    printf("name1[2] = %s\n", alphSwitchList[2].name1);
    printf("name2[2] = %s\n", alphSwitchList[2].name2);
    printf("episode[2] = %ld\n", alphSwitchList[2].episode);
    return 0;
}

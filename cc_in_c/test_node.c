typedef long fixed_t;
typedef struct {
    fixed_t x;
    fixed_t y;
    fixed_t dx;
    fixed_t dy;
    fixed_t bbox[8];
    unsigned long children[2];
} node_t;

node_t nodes[3];

int main() {
    printf("sizeof(node_t)=%ld\n", sizeof(node_t));
    printf("&nodes[0]=%p &nodes[1]=%p diff=%ld\n",
        &nodes[0], &nodes[1], (long)&nodes[1] - (long)&nodes[0]);

    nodes[0].x = 100;
    nodes[0].children[0] = 10;
    nodes[0].children[1] = 11;
    nodes[1].x = 200;
    nodes[1].children[0] = 20;

    node_t *p = &nodes[0];
    p++;
    printf("p->x=%ld (expect 200) p->children[0]=%ld (expect 20)\n", p->x, p->children[0]);
    if (p->x != 200 || p->children[0] != 20) {
        printf("FAIL\n");
        return 1;
    }
    printf("PASS\n");
    return 0;
}

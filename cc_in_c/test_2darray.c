typedef struct {
    long x;
    long y;
    long bbox[2][4];
    long children[2];
} node_t;

node_t n;

int main() {
    n.x = 10;
    n.y = 20;
    n.bbox[0][0] = 100;
    n.bbox[0][3] = 103;
    n.bbox[1][0] = 200;
    n.bbox[1][3] = 203;
    n.children[0] = 300;
    n.children[1] = 301;

    printf("sizeof(node_t)=%ld\n", sizeof(node_t));
    printf("children[0]=%ld children[1]=%ld\n", n.children[0], n.children[1]);
    printf("bbox[0][0]=%ld bbox[0][3]=%ld\n", n.bbox[0][0], n.bbox[0][3]);
    printf("bbox[1][0]=%ld bbox[1][3]=%ld\n", n.bbox[1][0], n.bbox[1][3]);

    if (n.children[0] != 300) { printf("FAIL children[0]=%ld\n", n.children[0]); return 1; }
    if (n.children[1] != 301) { printf("FAIL children[1]=%ld\n", n.children[1]); return 1; }
    printf("PASS\n");
    return 0;
}

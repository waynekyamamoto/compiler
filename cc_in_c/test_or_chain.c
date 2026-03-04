#include <stdio.h>

int main() {
    int x = 0;
    int y = 0;
    int w = 320;
    int h = 200;
    
    if (x < 0 || x + w > 320 || y < 0 || y + h > 200) {
        printf("FAIL: condition should be false\n");
        printf("x<0=%d x+w>320=%d y<0=%d y+h>200=%d\n", x<0, x+w>320, y<0, y+h>200);
    } else {
        printf("PASS: condition correctly false\n");
    }
    
    return 0;
}

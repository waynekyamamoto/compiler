// Test batch 53: #warning, #line, #pragma directives
int printf(int *fmt, ...);

#warning This is a test warning
#line 100
#pragma once

int main() {
    printf("batch53: all tests passed\n");
    return 0;
}

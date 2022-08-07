#include <stdio.h>
typedef short int16_t;
static int16_t a;
static int16_t b;
static int16_t c;
static int16_t d;
static int16_t e;
int main(void) {
    a = 1;
    b = 1;
    c = 200;
    d = 10.5;
    e = 1.3;
    printf("%d", a + b + d++);
    printf(" %d\n", e + c);

    return 0;
}

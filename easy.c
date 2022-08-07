#include <stdio.h>
typedef short int16_t;
static int16_t a;
static int16_t b;
int main(void) {
    a = 1.1;
    b = 10;
    printf("%d\n", a + b);

    return 0;
}

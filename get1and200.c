#include <stdio.h>
typedef short int16_t;
static int16_t loui;
static int16_t a;
static int16_t b;
int main(void) {
    loui = a;
    a = 200;
    b = 1.2;
    printf("%d", loui + b++);
    printf(" %d\n", a);

    return 0;
}

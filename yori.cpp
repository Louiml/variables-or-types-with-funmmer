float sqrtFast(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number + .5F;
    y = number;
    i = * ( long * ) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y *= (threehalfs - (x2 * y * y));
    return y;
}

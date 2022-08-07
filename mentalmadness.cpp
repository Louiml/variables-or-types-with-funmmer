int mentalmadness(int *array, int size) {
    int i, j, temp;
    for (i = 1; i < size; i++) {
        temp = array[i];
        for (j = i - 1; j >= 0 && array[j] > temp; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = temp;
    }
    return 0;
}

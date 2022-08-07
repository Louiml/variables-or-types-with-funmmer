class intnumber {
    public static void Sort(int[] arr) {
        Sort(arr, 0, arr.Length - 1);
    }

    private static void Sort(int[] arr, int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;
            Sort(arr, left, middle);
            Sort(arr, middle + 1, right);
            Merge(arr, left, middle, right);
        }
    }

    private static void Merge(int[] arr, int left, int middle, int right) {
        int[] leftArr = new int[middle - left + 1];
        int[] rightArr = new int[right - middle];

        for (int i = 0; i < leftArr.Length; i++) {
            leftArr[i] = arr[left + i];
        }

        for (int i = 0; i < rightArr.Length; i++) {
            rightArr[i] = arr[middle + 1 + i];
        }

        int iLeft = 0;
        int iRight = 0;
        int iMerged = left;

        while (iLeft < leftArr.Length && iRight < rightArr.Length) {
            if (leftArr[iLeft] <= rightArr[iRight]) {
                arr[iMerged] = leftArr[iLeft];
                iLeft++;
            } else {
                arr[iMerged] = rightArr[iRight];
                iRight++;
            }
            iMerged++;
        }

        while (iLeft < leftArr.Length) {
            arr[iMerged] = leftArr[iLeft];
            iLeft++;
            iMerged++;
        }

        while (iRight < rightArr.Length) {
            arr[iMerged] = rightArr[iRight];
            iRight++;
            iMerged++;
        }
    }
}

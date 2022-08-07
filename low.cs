private int low(int[] array, int size)
{
	int i;
	int j;
	int k;
	int temp;
	for (i = 1; i < size; i *= 2)
	{
		for (j = 0; j < size - i; j += 2 * i)
		{
			k = j + i;
			if (k > size - 1)
			{
				k = size - 1;
			}
			for (temp = j; temp < k; temp++)
			{
				if (array[temp] > array[k])
				{
					int temp2 = array[temp];
					array[temp] = array[k];
					array[k] = temp2;
				}
			}
		}
	}
	return 0;
}

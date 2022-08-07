static int32 Factorial(int32 n) => n <= 1 ? 1 : (n * Factorial(n - 1));
const int fac = Factorial(8); // Evaluates to 40320 at compile-time

public static Span<int32> GetSorted(String numList)
{
    List<int32> list = scope .();
    for (var sv in numList.Split(','))
        list.Add(int32.Parse(sv..Trim()));      
    return list..Sort();
}
const int32[?] iArr = GetSorted("8, 1, 3, 7");

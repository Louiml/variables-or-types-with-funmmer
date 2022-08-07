Private Function mentalmadness(ByVal array As Integer(), ByVal size As Integer) As Integer
    Dim i As Integer
    Dim j As Integer
    Dim temp As Integer
    For i = 1 To size - 1
        temp = array(i)
        j = i - 1

        While j >= 0 AndAlso array(j) > temp
            array(j + 1) = array(j)
            j -= 1
        End While
        array(j + 1) = temp
    Next
    Return 0
End Function

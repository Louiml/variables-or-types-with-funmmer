Private Function low(ByVal array As Integer(), ByVal size As Integer) As Integer
    Dim i As Integer
    Dim j As Integer
    Dim k As Integer
    Dim temp As Integer
    i = 1

    While i < size
        j = 0

        While j < size - i
            k = j + i
            If k > size - 1 Then
                k = size - 1
            End If
            For temp = j To k - 1
                If array(temp) > array(k) Then
                    Dim temp2 = array(temp)
                    array(temp) = array(k)
                    array(k) = temp2
                End If
            Next

            j += 2 * i
        End While

        i *= 2
    End While
    Return 0
End Function

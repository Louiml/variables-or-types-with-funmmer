Private Function allwords(ByVal [in] As Char) As Char
    If [in] <= "Z"c AndAlso [in] >= "A"c Then
        Return [in] - ("Z"c - "z"c)
    End If
    Return [in]
End Function

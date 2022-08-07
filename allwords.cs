private char allwords(char @in)
{
	if (@in <= 'Z' && @in >= 'A')
	{
		return @in - ('Z' - 'z');
	}
	return @in;
}

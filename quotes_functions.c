static char	*get_string_tok(char *start, char *end, int token_len)
{
	char	*token;
	char	*quoted_tok;
	char	*str_tok;
	char	tok_type;

	str_tok = NULL;
	token = get_non_quoted_tok(start, end, token_len);
	while (*g_sh.line && !is_special_char(*g_sh.line)
		&& !ft_isspace(*g_sh.line))
	{
		if (check_quote_in_str(start, end))
			return (NULL);
		if (g_sh.x == 1)
			tok_type = '\"';
		else if (g_sh.x == 2)
			tok_type = '\'';
		else
			return (NULL);
		quoted_tok = get_quoted_token(start, end, token_len, tok_type);
		token = ft_strjoin(token, quoted_tok);
		g_sh.line++;
		str_tok = get_non_quoted_tok(start, end, token_len);
		token = ft_strjoin(token, str_tok);
	}
	return (token);
}

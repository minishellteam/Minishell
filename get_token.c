/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/15 16:42:27 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_ex_code_token(char *token_start, int token_len)
{
	char	*token;

	token_len = 2;
	token_start = g_sh.line;
	token = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(token, token_start, token_len + 1);
	g_sh.line += 2;
	return (token);
}

char	*get_special_tok(char special_char, int token_len)
{
	char	special_tok[2];
	char	*token;

	if (*g_sh.line == '|' && *(g_sh.line + 1) == '|')
		get_error_message("|", 1);
	token = check_chevrons(token_len);
	if (token)
		return (token);
	token_len = 1;
	special_tok[0] = special_char;
	special_tok[1] = '\0';
	if (special_tok[0] == '&' || special_tok[0] == '*' || special_tok[0] == ';'
		|| special_tok[0] == '\\' || special_tok[0] == '['
		|| special_tok[0] == ']' || special_tok[0] == '{'
		|| special_tok[0] == '}')
		get_error_message(special_tok, 0);
	if (special_tok[0] == '?')
		if (*(g_sh.line - 1) != '$')
			get_error_message(special_tok, 0);
	token = malloc(sizeof(char) * (token_len + 1));
	ft_strlcpy(token, special_tok, token_len + 1);
	g_sh.line++;
	return (token);
}

int	check_quote_in_str(void)
{
	int	x;

	x = 0;
	if (*g_sh.line == '\"')
	{
		g_sh.line++;
		if (!ft_strchr(g_sh.line, '\"'))
			get_error_message(NULL, 2);
		while (*g_sh.line && *g_sh.line != '\"')
			g_sh.line++;
		x = 1;
	}
	else if (*g_sh.line == '\'')
	{
		g_sh.line++;
		if (!ft_strchr(g_sh.line, '\''))
			get_error_message(NULL, 2);
		while (*g_sh.line && *g_sh.line != '\'')
			g_sh.line++;
	}
	printf("x = %d\n", x);
	return (x);
}

char	*remove_quotes(char *token)
{
	int		i;
	char	*before_quote;
	char	*after_quote;
	
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\"')
		{
			before_quote = ft_substr(token, 0, i + 1);
			after_quote = ft_substr(token, i + 1, ft_strlen(token) - i + 1);
			token = ft_strjoin(before_quote, after_quote);
		}
	}
	return (token);
}

char	*get_string_tok(char *token_start, char *token_end, int token_len)
{
	char	*token;
	char	*var;
	char	*value;
	int		x;

	token = NULL;
	var = NULL;
	value = NULL;
	x = 0;
	while (*g_sh.line && !is_special_char(*g_sh.line) && !ft_isspace(*g_sh.line))
	{
		g_sh.line++;
		x = check_quote_in_str();
	}
	token_end = g_sh.line;
	token_len = token_end - token_start;
	token = malloc(sizeof(char) * (token_len + 1));
	ft_strlcpy(token, token_start, token_len + 1);
	token = remove_quotes(token);
	if (x == 1)
		token = handle_var(token, var, value);
	return (token);
}

char	*get_token(char *token_start)
{
	char	*token;
	char	*token_end;
	int		token_len;

	token = NULL;
	token_len = 0;
	token_end = NULL;
	while (ft_isspace(*g_sh.line))
		g_sh.line++;
	token_start = g_sh.line;
	if (*g_sh.line == '\"' || *g_sh.line == '\'')
		token = get_quoted_token(token_start, token_end, token_len);
	else if (is_special_char(*g_sh.line))
		token = get_special_tok(*g_sh.line, token_len);
	else if (*g_sh.line == '$' && *(g_sh.line + 1) == '?')
		token = get_ex_code_token(g_sh.line, token_len);
	else
		token = get_string_tok(token_start, token_end, token_len);
	return (token);
}

void	tokenize_line(void)
{
	t_tok	*tokens;
	t_tok	*tok;
	char	*token;
	char	*token_start;

	tokens = NULL;
	if (*g_sh.line == '?')
		get_error_message("?", 0);
	while (*g_sh.line)
	{
		token_start = g_sh.line;
		token = get_token(token_start);
		tok = ft_lst_new(token);
		ft_lst_add_back(&tokens, tok);
		while (ft_isspace(*g_sh.line))
			g_sh.line++;
	}
	g_sh.tokens = tokens;
	print_list(tokens);
}

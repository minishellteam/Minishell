/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/23 10:35:59 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_ex_code_token(char *token_start, int token_len)
{
	char	*token;

	token_len = 2;
	token_start = g_sh.line;
	token = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(token, token_start, token_len + 1);
	g_sh.line += 2;
	return (token);
}

static char	*get_special_tok(char special_char, int token_len)
{
	char	special_tok[2];
	char	*token;

	if (*g_sh.line == '|' && *(g_sh.line + 1) == '|')
	{
		get_error_message("|", 1);
		return (NULL);
	}
	token = get_double_chevrons_token(token_len);
	if (token)
		return (token);
	token_len = 1;
	special_tok[0] = special_char;
	special_tok[1] = '\0';
	if (is_forbidden_char(special_tok[0]))
	{
		get_error_message(special_tok, 0);
		return (NULL);
	}
	if (check_question_mark(special_tok))
		return (NULL);
	token = malloc(sizeof(char) * (token_len + 1));
	ft_strlcpy(token, special_tok, token_len + 1);
	g_sh.line++;
	return (token);
}

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
		token = ft_strjoin(token, quoted_tok, 0);
		g_sh.line++;
		str_tok = get_non_quoted_tok(start, end, token_len);
		token = ft_strjoin(token, str_tok, 0);
	}
	return (token);
}

static char	*get_token(char *token_start)
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
	if (is_special_char(*g_sh.line))
		token = get_special_tok(*g_sh.line, token_len);
	else if (*g_sh.line == '$' && *(g_sh.line + 1) == '?')
		token = get_ex_code_token(g_sh.line, token_len);
	else
		token = get_string_tok(token_start, token_end, token_len);
	return (token);
}

void	tokenize_line(void)
{
	t_tok	*toks;
	t_tok	*tok;
	char	*token;
	char	*token_start;

	toks = NULL;
	if (*g_sh.line == '?')
	{
		get_error_message("?", 0);
		return ;
	}
	while (*g_sh.line)
	{
		token_start = g_sh.line;
		token = get_token(token_start);
		if (!token)
			return ;
		tok = ft_lst_new(token);
		ft_lst_add_back(&toks, tok);
		while (ft_isspace(*g_sh.line))
			g_sh.line++;
	}
	g_sh.toks = toks;
	//print_list(g_sh.toks, 0);
	g_sh.toks = get_token_type(g_sh.toks);
	//print_list(g_sh.toks, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/07/05 16:02:01 by mkerkeni         ###   ########.fr       */
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

static char	*get_string_tok(char *token_start, char *token_end, int token_len)
{
	char	*token;
	char	*quote;

	token = NULL;
	token_start = g_sh.line;
	while (*g_sh.line && !ft_isspace(*g_sh.line) 
		&& !is_special_char(*g_sh.line))
	{
		if (*g_sh.line == '\"' || *g_sh.line == '\'')
		{
			quote = g_sh.line;
			if ((*g_sh.line == '\"' && *(g_sh.line + 1) == '\"')
				|| (*g_sh.line == '\'' && *(g_sh.line + 1) == '\''))
			{
				g_sh.line += 2;
				token = "";
				return (token);
			}
			if (check_quote_in_str(token_start, token_end))
				return (NULL);
			g_sh.line++;
			while (*g_sh.line != *quote)
				g_sh.line++;
		}
		g_sh.line++;
	}
	token_end = g_sh.line - 1;
	token_len = token_end - token_start + 1;
	token = malloc(sizeof(char) * (token_len + 1));
	ft_strlcpy(token, token_start, token_len + 1);
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
		while (*g_sh.line && ft_isspace(*g_sh.line))
			g_sh.line++;
	}
	g_sh.toks = toks;
	g_sh.toks = get_token_type(g_sh.toks);
	handle_quotes();
	parse_tokens();
}

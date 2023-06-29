/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:32:50 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/29 15:04:53 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*get_non_quoted_tok(char *token_start, char *token_end, int token_len)
// {
// 	char	*str_tok;
// 	char	*var;
// 	char	*value;

// 	str_tok = NULL;
// 	var = NULL;
// 	value = NULL;
// 	if (*g_sh.line && *g_sh.line != '\'' && *g_sh.line != '\"'
// 		&& !ft_isspace(*g_sh.line) && !is_special_char(*g_sh.line))
// 	{
// 		token_start = g_sh.line;
// 		while (*g_sh.line && *g_sh.line != '\'' && *g_sh.line != '\"'
// 			&& !ft_isspace(*g_sh.line) && !is_special_char(*g_sh.line))
// 			g_sh.line++;
// 		token_end = g_sh.line - 1;
// 		token_len = token_end - token_start + 1;
// 		str_tok = malloc(sizeof(char) * (token_len + 1));
// 		ft_strlcpy(str_tok, token_start, token_len + 1);
// 		str_tok = search_and_replace_var(str_tok, var, value);
// 	}
// 	else
// 		str_tok = "";
// 	return (str_tok);
// }

// char	*get_quoted_token(char *start, char *end, int token_len, char q_type)
// {
// 	char	*quoted_token;
// 	char	*var;
// 	char	*value;

// 	quoted_token = NULL;
// 	var = NULL;
// 	value = NULL;
// 	start = g_sh.line;
// 	while (*g_sh.line && *g_sh.line != q_type)
// 		g_sh.line++;
// 	end = g_sh.line - 1;
// 	token_len = end - start + 1;
// 	quoted_token = malloc(sizeof(char) * (token_len + 1));
// 	ft_strlcpy(quoted_token, start, token_len + 1);
// 	if (q_type == '\"')
// 		quoted_token = search_and_replace_var(quoted_token, var, value);
// 	return (quoted_token);
// }

int	check_quote_in_str(char *token_start, char *token_end)
{
	char	token_type;

	token_type = 0;
	if (*g_sh.line == '\"')
	{
		token_type = '\"';
		g_sh.x = 1;
	}
	else if (*g_sh.line == '\'')
	{
		token_type = '\'';
		g_sh.x = 2;
	}
	g_sh.line++;
	token_start = g_sh.line;
	token_end = g_sh.line;
	if (!ft_strchr(g_sh.line, token_type))
	{
		get_error_message(NULL, 2);
		return (1);
	}
	while (*token_end && *token_end != token_type)
		token_end++;
	token_end++;
	return (0);
}

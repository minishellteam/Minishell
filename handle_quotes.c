/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 10:32:50 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/15 11:52:15 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_and_replace_var(char *token, char *var)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	value = NULL;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?')
				i++;
			var = ft_substr(token, j, i - j);
			//if (var == '?')
			//	value = get_ex_code_value();	
			value = getenv(var);
			free(var);
			token = replace_var_by_value(token, value, j, i);
			i = 0;
		}
		else
			i++;
	}
	return (token);
}

char	*get_s_quote_tok(char *token_start, char *token_end, int token_len)
{
	char	*token;

	token = NULL;
	token_start = g_sh.line + 1;
	g_sh.line++;
	if (!ft_strchr(token_start, '\''))
		get_error_message(NULL, 2);
	while (*g_sh.line && *g_sh.line != '\'')
		g_sh.line++;
	token_end = g_sh.line;
	token_len = token_end - token_start;
	token = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(token, token_start, token_len + 1);
	g_sh.line++;
	return (token);
}

char	*get_quoted_token(char *token_start, char *token_end, int token_len)
{
	char	*token;
	char	*tmp_tok;
	char	*var;

	token = NULL;
	token_len = 0;
	var = NULL;
	if (*g_sh.line == '\'')
		token = get_s_quote_tok(token_start, token_end, token_len);
	else if (*g_sh.line == '\"')
	{
		token_start = g_sh.line + 1;
		g_sh.line++;
		if (!ft_strchr(token_start, '\"'))
			get_error_message(NULL, 2);
		while (*g_sh.line && *g_sh.line != '\"')
			g_sh.line++;
		token_end = g_sh.line;
		token_len = token_end - token_start;
		tmp_tok = malloc(sizeof(char) * token_len + 1);
		ft_strlcpy(tmp_tok, token_start, token_len + 1);
		g_sh.line++;
		token = search_and_replace_var(tmp_tok, var);
	}
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:43:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/15 11:53:38 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char token)
{
	if (token == '|' || token == '<' || token == '>' || token == '\\'
		|| token == ';' || token == '&' || token == '*' || token == '['
		|| token == ']' || token == '{' || token == '}' || token == '?')
		return (1);
	return (0);
}

int	ft_isspace(char token)
{
	if (token == ' ' || token == '\t' || token == '\n' || token == '\f'
		|| token == '\v' || token == '\r')
		return (1);
	return (0);
}

char	*check_chevrons(int token_len)
{
	char	*token;

	token = NULL;
	if ((*g_sh.line == '>' && *(g_sh.line + 1) == '>')
		|| (*g_sh.line == '<' && *(g_sh.line + 1) == '<'))
	{
		if (*(g_sh.line + 2) == '>' || *(g_sh.line + 2) == '<')
		{
			if (*(g_sh.line + 3) == '>')
				get_error_message(">>", 1);
			else if (*(g_sh.line + 3) == '<')
				get_error_message("<<", 1);
			else
				get_error_message(g_sh.line + 2, 1);
		}
		token = get_double_chevron_token(token_len);
	}
	else if ((*g_sh.line == '>' && *(g_sh.line + 1) == '<'))
		get_error_message(g_sh.line + 1, 1);
	else if (*g_sh.line == '<' && *(g_sh.line + 1) == '>'
		&& *(g_sh.line + 2) == '>')
		get_error_message(g_sh.line + 2, 1);
	return (token);
}

char	*get_double_chevron_token(int token_len)
{
	char	*token;

	token_len = 2;
	token = malloc(sizeof(char) * token_len + 1);
	ft_strlcpy(token, g_sh.line, token_len + 1);
	g_sh.line += 2;
	return (token);
}

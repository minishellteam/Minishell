/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:43:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/07/04 16:47:15 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_special_char(char token)
{
	if (token == '|' || token == '<' || token == '>' || token == '\\'
		|| token == ';' || token == '&' || token == '*' || token == '['
		|| token == ']' || token == '{' || token == '}' || token == '?'
		|| token == '(' || token == ')')
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

int	is_forbidden_char(char token)
{
	if (token == '&' || token == '*' || token == ';' || token == '\\'
		|| token == '[' || token == ']' || token == '{' || token == '}'
		|| token == '(' || token == ')')
		return (1);
	return (0);
}

int	check_question_mark(char *token)
{
	if (token[0] == '?')
	{
		if (*(g_sh.line - 1) != '$')
		{
			get_error_message(token, 0);
			return (1);
		}
	}
	return (0);
}

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

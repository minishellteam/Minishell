/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 11:43:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/19 14:33:18 by mkerkeni         ###   ########.fr       */
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

int	is_forbidden_char(char token)
{
	if (token == '&' || token == '*' || token == ';' || token == '\\'
		|| token == '[' || token == ']' || token == '{' || token == '}')
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

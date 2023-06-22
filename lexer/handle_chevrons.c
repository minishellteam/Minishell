/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chevrons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:32:56 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/22 17:07:39 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_chevron(char	*token, int x)
{
	if (x == 0)
	{
		if (!ft_strncmp(token, "GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "DOUBLE_GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "LESSER", ft_strlen(token))
			|| !ft_strncmp(token, "DOUBLE_LESSER", ft_strlen(token))
			|| !ft_strncmp(token, "PIPE", ft_strlen(token)))
			return (1);
	}
	else
	{
		if (!ft_strncmp(token, "GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "DOUBLE_GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "LESSER", ft_strlen(token))
			|| !ft_strncmp(token, "DOUBLE_LESSER", ft_strlen(token)))
			return (1);
	}
	return (0);
}

static void	check_next_tok(char *next_tok, char *token)
{
	if (is_chevron(next_tok, 0))
		get_error_message(token, 1);
}

int	check_chevrons(t_tok *pipeline)
{
	t_tok	*tmp;

	tmp = pipeline;

	while (tmp)
	{
		if (is_chevron(tmp->type, 0) && !tmp->next)
		{
			printf("PASS\n");
			get_error_message(tmp->tok, 1);
			return (1);
		}
		if (!ft_strncmp(tmp->type, "GREATER", ft_strlen(tmp->type)))
			check_next_tok(tmp->next->type, ">");
		else if (!ft_strncmp(tmp->type, "DOUBLE_GREATER", ft_strlen(tmp->type)))
			check_next_tok(tmp->next->type, ">>");
		else if (!ft_strncmp(tmp->type, "LESSER", ft_strlen(tmp->type)))
			check_next_tok(tmp->next->type, "<");
		else if (!ft_strncmp(tmp->type, "DOUBLE_LESSER", ft_strlen(tmp->type)))
			check_next_tok(tmp->next->type, "<<");
		if (is_chevron(tmp->type, 0) && is_chevron(tmp->next->type, 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_double_chevrons_token(int token_len)
{
	char	*token;

	token_len = 2;
	token = NULL;
	if ((*g_sh.line == '>' && *(g_sh.line + 1) == '>')
		|| (*g_sh.line == '<' && *(g_sh.line + 1) == '<'))
	{
		token = malloc(sizeof(char) * token_len + 1);
		ft_strlcpy(token, g_sh.line, token_len + 1);
		g_sh.line += 2;
	}
	return (token);
}

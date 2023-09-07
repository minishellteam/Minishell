/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_chevrons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:32:56 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/07 09:31:59 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_chevron(char	*token, int x)
{
	if (x == 0)
	{
		if (!ft_strncmp(token, "GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "D_GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "LESSER", ft_strlen(token))
			|| !ft_strncmp(token, "D_LESSER", ft_strlen(token))
			|| !ft_strncmp(token, "PIPE", ft_strlen(token)))
			return (1);
	}
	else
	{
		if (!ft_strncmp(token, "GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "D_GREATER", ft_strlen(token))
			|| !ft_strncmp(token, "LESSER", ft_strlen(token))
			|| !ft_strncmp(token, "D_LESSER", ft_strlen(token)))
			return (1);
	}
	return (0);
}

static int	check_next_tok(char *next_tok, char *token)
{
	if (is_chevron(next_tok, 0))
	{
		get_error_message(token, 1);
		return (1);
	}
	return (0);
}

static int	check_multiple_chevrons(t_tok *tmp)
{
	if (!ft_strncmp(tmp->type, "GREATER", ft_strlen(tmp->type)))
	{
		if (check_next_tok(tmp->next->type, ">"))
			return (1);
	}
	else if (!ft_strncmp(tmp->type, "D_GREATER", ft_strlen(tmp->type)))
	{
		if (check_next_tok(tmp->next->type, ">>"))
			return (1);
	}
	else if (!ft_strncmp(tmp->type, "LESSER", ft_strlen(tmp->type)))
	{
		if (check_next_tok(tmp->next->type, "<"))
			return (1);
	}
	else if (!ft_strncmp(tmp->type, "D_LESSER", ft_strlen(tmp->type)))
	{
		if (check_next_tok(tmp->next->type, "<<"))
			return (1);
	}
	return (0);
}

int	check_chevrons(t_vars *var)
{
	t_tok	*tmp;

	tmp = var->pipeline;
	while (tmp && ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
	{
		if (is_chevron(tmp->type, 1) && !tmp->next)
		{
			get_error_message(tmp->tok, 1);
			return (1);
		}
		if (check_multiple_chevrons(tmp))
			return (1);
		if (tmp && tmp->next && is_chevron(tmp->type, 0)
			&& is_chevron(tmp->next->type, 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	*get_double_chevrons_token(t_vars *var)
{
	char	*token;

	var->len = 2;
	token = NULL;
	if ((*(var->line) == '>' && *(var->line + 1) == '>')
		|| (*(var->line) == '<' && *(var->line + 1) == '<'))
	{
		token = malloc(sizeof(char) * var->len + 1);
		ft_strlcpy(token, var->line, var->len + 1);
		var->line += 2;
	}
	return (token);
}

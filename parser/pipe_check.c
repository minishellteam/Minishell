/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:49:56 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/09 00:58:47 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_before_pipe(t_tok *pipeline)
{
	t_tok	*tmp;

	tmp = pipeline;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
		{
			if (!tmp->prev)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	get_nb_of_pipes(t_tok *toks)
{
	t_tok	*tmp;
	int		pipe_nb;

	tmp = toks;
	pipe_nb = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
			pipe_nb++;
		tmp = tmp->next;
	}
	return (pipe_nb);
}

int	check_double_pipe(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp && tmp->next)
	{
		if (!ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
		{
			if (!ft_strncmp(tmp->next->type, "PIPE", ft_strlen(tmp->type)))
			{
				get_error_message("|", 1);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

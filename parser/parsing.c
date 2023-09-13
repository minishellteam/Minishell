/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:06:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/28 22:25:30 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_pipeline(t_vars *var)
{
	if (!var->pipeline)
	{
		get_error_message("|", 1);
		return (1);
	}
	if (check_before_pipe(var))
	{
		get_error_message("|", 1);
		return (1);
	}
	if (check_chevrons(var))
		return (1);
	return (0);
}

static void	get_pipeline(t_vars *var)
{
	while (var->pipeline_end && var->pipeline_end->next
		&& ft_strncmp(var->pipeline_end->type, "PIPE", \
			ft_strlen(var->pipeline_end->type)))
		var->pipeline_end = var->pipeline_end->next;
}

int	parse_tokens(t_vars *var)
{
	int				pipe_nb;
	int				i;

	var->pipeline = var->toks;
	var->pipeline_end = var->toks;
	if (check_double_pipe(var->toks))
		return (1);
	pipe_nb = get_nb_of_pipes(var->toks);
	var->pipe_nb = pipe_nb;
	i = -1;
	while (++i <= pipe_nb)
	{
		get_pipeline(var);
		if (parse_pipeline(var))
			return (1);
		var->pipeline_end = var->pipeline_end->next;
		var->pipeline = var->pipeline_end;
	}
	get_files(var->toks);
	return (0);
}

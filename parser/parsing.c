/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:06:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/10 00:25:12 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_pipeline(t_tok *pipeline)
{
	if (!pipeline)
	{
		get_error_message("|", 1);
		return (0);
	}
	if (check_before_pipe(pipeline))
	{
		get_error_message("|", 1);
		return (1);
	}
	if (check_chevrons(pipeline))
		return (1);
	return (0);
}

static t_tok	*get_pipeline(t_vars *var)
{
	t_tok	*pipeline;
	t_tok	*end;

	pipeline = var->rest;
	end = var->rest;
	while (end && end->next
		&& ft_strncmp(end->type, "PIPE", ft_strlen(end->type)))
		end = end->next;
	if (end && end->next)
	{
		var->rest = end->next;
		end->next = NULL;
	}
	else
		var->rest = NULL;
	return (pipeline);
}

static t_tok	*get_copy_tokens(t_tok *toks)
{
	t_tok	*new_tok;
	t_tok	*toks_cpy;
	t_tok	*tmp;

	tmp = toks;
	toks_cpy = NULL;
	while (tmp)
	{
		new_tok = ft_lst_new(tmp->tok);
		ft_lst_add_back(&toks_cpy, new_tok);
		tmp = tmp->next;
	}
	toks_cpy = get_token_type(toks_cpy);
	return (toks_cpy);
}

int	parse_tokens(t_vars *var)
{
	t_tok			*pipeline;
	int				pipe_nb;
	int				i;
	t_tok			*toks_cpy;

	if (check_double_pipe(var->toks))
		return (1);
	toks_cpy = get_copy_tokens(var->toks);
	var->rest = toks_cpy;
	pipe_nb = get_nb_of_pipes(var->toks);
	i = -1;
	while (++i <= pipe_nb)
	{
		pipeline = get_pipeline(var);
		if (parse_pipeline(pipeline))
			return (1);
	}
	free_list(toks_cpy);
	free_list(var->rest);
	get_files(var->toks);
	return (0);
}

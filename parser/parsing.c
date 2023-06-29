/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:06:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/22 15:34:03 by mkerkeni         ###   ########.fr       */
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
	if (check_chevrons(pipeline))
		return (1);
	return (0);
}

t_tok	*get_pipeline(void)
{
	t_tok	*pipeline;
	t_tok	*end;

	pipeline = g_sh.rest;
	end = g_sh.rest;
	while (end && end->next
		&& ft_strncmp(end->type, "PIPE", ft_strlen(end->type)))
		end = end->next;
	if (end && end->next)
	{
		g_sh.rest = end->next;
		end->next = NULL;
	}
	else
		g_sh.rest = NULL;
	return (pipeline);
}

static int	get_nb_of_pipes(void)
{
	t_tok	*tmp;
	int		pipe_nb;

	tmp = g_sh.toks;
	pipe_nb = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
			pipe_nb++;
		tmp = tmp->next;
	}
	return (pipe_nb);
}

static t_tok	*get_copy_tokens(void)
{
	t_tok	*new_tok;
	t_tok	*toks_cpy;
	t_tok	*tmp;

	tmp = g_sh.toks;
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

void	parse_tokens(void)
{
	t_tok	*pipeline;
	int		pipe_nb;
	int		i;
	t_tok	*toks_cpy;

	//remove_empty_tok();
	toks_cpy = get_copy_tokens();
	g_sh.rest = toks_cpy;
	pipe_nb = get_nb_of_pipes();
	i = -1;
	while (++i <= pipe_nb)
	{
		pipeline = get_pipeline();
		if (parse_pipeline(pipeline))
			return ;
	}
	get_options();
	get_files();
	get_commands();
	get_arguments();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:59:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/30 14:23:50 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_input(t_vars *var, int i)
{
	t_input	*tmp;
	char	*exp_input;

	var->var = NULL;
	var->value = NULL;
	exp_input = NULL;
	tmp = var->data[i];
	while (tmp)
	{
		exp_input = get_var(tmp->input, var, 0, 0);
		tmp->input = ft_strdup(exp_input);
		free(exp_input);
		tmp = tmp->next;
	}
}

static int	here_doc_loop(t_vars *var, char *line, char *limiter, t_input *data)
{
	while (line)
	{
		line = readline("> ");
		line = ft_strjoin(line, "\n", 1);
		if (*get_exit_status() == 130)
		{
			var->data[var->i] = data;
			free(line);
			free(limiter);
			signal(SIGINT, basic_signal);
			return (1);
		}
		if (!line || !ft_strcmp(line, limiter))
		{
			var->data[var->i] = data;
			break ;
		}
		ft_lstadd_back_input(&data, ft_lstnew_input(line));
	}
	return (0);
}

static int	get_input(t_vars *var, char *limiter, int i)
{
	char	*line;
	t_input	*data;

	signal(SIGINT, here_doc_signal);
	var->i = i;
	limiter = ft_strjoin(limiter, "\n", 0);
	line = readline("> ");
	line = ft_strjoin(line, "\n", 1);
	if (!line || !ft_strcmp(line, limiter) || *get_exit_status() == 130)
	{
		free(line);
		free(limiter);
		signal(SIGINT, basic_signal);
		return (1);
	}
	data = ft_lstnew_input(line);
	if (here_doc_loop(var, line, limiter, data))
		return (1);
	signal(SIGINT, basic_signal);
	//free(line);
	free(limiter);
	return (0);
}

int	handle_here_doc(t_vars *var, t_tok *tmp, int i)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->type, "PIPE"))
			i++;
		if (!ft_strcmp(tmp->type, "LIMITER"))
		{
			if (ft_strchr(tmp->tok, '\"') || ft_strchr(tmp->tok, '\''))
			{
				tmp = remove_quotes_limiter(tmp);
				if (get_input(var, tmp->tok, i))
					return (1);
			}
			else
			{
				if (!get_input(var, tmp->tok, i))
					expand_input(var, i);
				else
					return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

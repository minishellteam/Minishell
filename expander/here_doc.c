/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:59:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/29 19:28:48 by mkerkeni         ###   ########.fr       */
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

static int	get_input(t_vars *var, char *limiter, int i)
{
	char	*line;
	t_input	*data;

	limiter = ft_strjoin(limiter, "\n", 0);
	line = get_next_line(0);
	if (!line || !ft_strcmp(line, limiter))
	{
		free(line);
		free(limiter);
	}
	data = ft_lstnew_input(line);
	while (line)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, here_doc_signal);
		if (*get_exit_status() == 130) // exit status vaut 0 ici don't know why
		{
			free(line);
			free(limiter);
			return (1);
		}
		line = get_next_line(0);
		if (!line || !ft_strcmp(line, limiter))
		{
			var->data[i] = data;
			break ;
		}
		ft_lstadd_back_input(&data, ft_lstnew_input(line));
	}
	free(line);
	free(limiter);
	return (0);
}

static t_tok	*remove_quotes_limiter(t_tok *tmp)
{
	int		i;
	char	*before_quote;
	char	*after_quote;
	char	*new_tok;

	i = 0;
	new_tok = ft_strdup(tmp->tok);
	while (new_tok[i])
	{
		if (new_tok[i] == '\"' || new_tok[i] == '\'')
		{
			before_quote = ft_substr(new_tok, 0, i);
			after_quote = ft_substr(new_tok, i + 1, ft_strlen(new_tok) - i);
			free(new_tok);
			new_tok = ft_strjoin(before_quote, after_quote, 2);
			i = 0;
		}
		else
			i++;
	}
	ft_strcpy(tmp->tok, new_tok);
	free(new_tok);
	return (tmp);
}

static int	handle_here_doc(t_vars *var, t_tok *tmp, int i)
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

int	check_limiter(t_vars *var)
{
	t_tok	*tmp;
	int		i;

	tmp = var->toks;
	var->data = (t_input **)ft_malloc(sizeof(t_input *) * (var->pipe_nb + 2));
	init_data(var);
	i = 0;
	if (handle_here_doc(var, tmp, i))
		return (1);
	return (0);
}

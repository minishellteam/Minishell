/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 22:59:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/14 12:18:49 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand_input(t_vars *var)
{
	t_input	*tmp;
	char	*exp_input;

	var->var = NULL;
	var->value = NULL;
	exp_input = NULL;
	tmp = var->data;
	while (tmp)
	{
		exp_input = get_var(tmp->input, var->var, var->value, 0);
		tmp->input = ft_strdup(exp_input);
		free(exp_input);
		tmp = tmp->next;
	}
}

static int	is_limiter(char *line, char *limiter)
{
	if (!ft_strncmp(line, limiter, ft_strlen(line)))
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			return (1);
	return (0);
}

static int	get_input(t_vars *var, char *limiter)
{
	char	*line;
	t_input	*data;

	limiter = ft_strjoin(limiter, "\n", 0);
	line = get_next_line(0);
	if (!line || is_limiter(line, limiter))
	{
		free(line);
		free(limiter);
		return (1);
	}
	data = ft_lstnew_input(line);
	while (line)
	{
		line = get_next_line(0);
		if (is_limiter(line, limiter))
		{
			var->data = data;
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

int	check_limiter(t_vars *var)
{
	t_tok	*tmp;

	tmp = var->toks;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "LIMITER", ft_strlen(tmp->type)))
		{
			if (ft_strchr(tmp->tok, '\"') || ft_strchr(tmp->tok, '\''))
			{
				tmp = remove_quotes_limiter(tmp);
				get_input(var, tmp->tok);
			}
			else
			{
				if (!get_input(var, tmp->tok))
					expand_input(var);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

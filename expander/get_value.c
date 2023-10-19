/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:24:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/19 12:56:03 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_value(t_vars *var, int bool)
{
	char	*value;

	value = get_value(var);
	if (bool == 1)
	{
		var->value = ft_strtrim(value, " ");
		free(value);
		if (var->y == 1)
			var->value = ft_strjoin(" ", var->value, 3);
	}
	else
		var->value = value;
}

char	*get_env(t_vars *var, char *variable)
{
	char	*value;
	int		i;
	int		j;

	i = -1;
	j = 0;
	value = NULL;
	while (var->sh->expenv[++i])
	{
		if (!strncmp(variable, var->sh->expenv[i], ft_strlen(variable)))
		{
			while (var->sh->expenv[i][j] && var->sh->expenv[i][j] != '=')
				j++;
			value = ft_substr(var->sh->expenv[i], j + 1, \
			ft_strlen(var->sh->expenv[i]) - j);
			return (value);
		}
	}
	value = ft_strdup("");
	return (value);
}

char	*get_value(t_vars *var)
{
	char	*value;

	if (!ft_strcmp(var->var, "?"))
		value = ft_itoa(*get_exit_status());
	else
		value = get_env(var, var->var);
	return (value);
}

char	*replace_var_by_value(char *line, char *value, int start, int end)
{
	char	*before_dollar;
	char	*after_var;
	char	*tmp;

	tmp = NULL;
	before_dollar = ft_substr(line, 0, start - 1);
	after_var = ft_substr(line, end, ft_strlen(line) - end);
	if (!value)
		line = ft_strjoin(before_dollar, after_var, 2);
	else
	{
		if (!before_dollar)
			tmp = value;
		else
			tmp = ft_strjoin(before_dollar, value, 1);
		if (!after_var)
			line = tmp;
		else
			line = ft_strjoin(tmp, after_var, 2);
	}
	return (line);
}

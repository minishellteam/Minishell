/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:24:41 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/06 15:14:36 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(t_vars *var, char *variable)
{
	char	*value;
	int		i;
	int		j;

	i = -1;
	j = 0;
	value = NULL;
	while (var->my_env[++i])
	{
		if (!strncmp(variable, var->my_env[i], ft_strlen(variable)))
		{
			while (var->my_env[i][j] && var->my_env[i][j] != '=')
				j++;
			value = ft_substr(var->my_env[i], j + 1, \
			ft_strlen(var->my_env[i]) - j);
			printf("value = %s\n", value);
			return (value);
		}
	}
	value = ft_strdup("");
	return (value);
}

void	get_value(t_vars *var)
{
	if (!ft_strcmp(var->var, "?"))
	{
		var->value = ft_itoa(*get_exit_status());
		var->bool = 1;
	}
	else if (!ft_strcmp(var ->var, "$"))
		var->value = ft_strdup("");
	else
		var->value = get_env(var, var->var);
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

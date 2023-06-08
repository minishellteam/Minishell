/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:16:52 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/08 10:16:33 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_var_by_value(char *line, char *value, int start, int end)
{
	char	*before_dollar;
	char	*after_var;

	before_dollar = ft_substr(line, 0, start - 1);
	after_var = ft_substr(line, end, ft_strlen(line) - end);
	if (!value)
		line = ft_strjoin(before_dollar, after_var);
	else
	{
		line = ft_strjoin(before_dollar, value);
		line = ft_strjoin(line, after_var);
	}
	return (line);
}

static char	*handle_var(char *new_line, char *var, char *value)
{
	int		i;
	int		j;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(new_line[i]) || new_line[i] == '_')
				i++;
			var = ft_substr(new_line, j, i - j);
			value = getenv(var);
			new_line = replace_var_by_value(new_line, value, j, i);
			var = NULL;
			value = NULL;
			i = 0;
		}
		else
			i++;
	}
	return (new_line);
}

char	*get_value_vars(t_command cmd)
{
	char	*new_line;
	char	*var;
	char	*value;

	var = NULL;
	value = NULL;
	new_line = ft_strdup(cmd.line);
	new_line = handle_var(new_line, var, value);
	printf("newline = %s\n", new_line);
	cmd.var_line = new_line;
	return (new_line);
}

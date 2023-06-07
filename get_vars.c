/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:16:52 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/07 16:05:41 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_var_by_nothing(char *s, int var_len)
{
	char	*final;
	int		i;
	int		k;
	
	final = malloc(sizeof(char) * (ft_strlen(s) - var_len - 1) + 1);
	i = 0;
	k = 0;
	while (s[i] && s[i] != '$')
	{
		final[k] = s[i];
		i++;
		k++;
	}
	if (s[i] && s[i] == '$' && s[i + 1])
	{
		i++;
		while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
			i++;
	}
	while (s[i])
	{
		final[k] = s[i];
		i++;
		k++;
	}
	final[k] = '\0';
	return (final);
}

char	*get_var(char *src, int start, int end)
{
	int		j;
	char	*var;

	var = malloc(sizeof(char) * (end - start) + 1);
	j = 0;
	while (start < end)
	{
		var[j] = src[start];
		j++;
		start++;
	}
	var[j] = '\0';
	return (var);
}
static char	*replace_var_by_value(char *new_line, char *value, int start, int end)
{
	char	*before_dollar;
	char	*after_var;
	
	before_dollar = ft_substr(new_line, 0, start - 1);
	after_var = ft_substr(new_line, end, ft_strlen(new_line) - end);
	printf("before_dollar = %s\n", before_dollar);
	printf("after_var = %s\n", after_var);
	new_line = ft_strjoin(before_dollar, value);
	new_line = ft_strjoin(new_line, after_var);
	return (new_line);	
}

static char	*handle_var(char *new_line, char *cmd_line, char *var, char *value)
{
	int		i;
	int		j;

	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(cmd_line[i]) || cmd_line[i] == '_')
				i++;
			var = get_var(cmd_line, j, i);
			value = getenv(var);
			if (!value)
				new_line = replace_var_by_nothing(new_line, ft_strlen(var));
			else
				new_line = replace_var_by_value(new_line, value, j, i);
			var = NULL;
			value = NULL;
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
	new_line = ft_strdup(cmd.cmd_line);
	new_line = handle_var(new_line, cmd.cmd_line, var, value);
	printf("newline = %s\n", new_line);
	return (cmd.cmd_line);
}

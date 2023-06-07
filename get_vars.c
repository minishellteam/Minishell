/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:16:52 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/07 12:13:13 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_var_by_value(char *s, char *value, int var_len)
{
	int		i;
	int		j;
	int		k;
	char	*final;

	i = 0;
	j = 0;
	k = 0;
	final = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(value) - var_len - 1) + 1);
	if (!final)
		handle_error("Malloc failure\n");	
	while (s[i] && s[i] != '$')
	{
		final[k] = s[i];
		i++;
		k++;
	}
	if (s[i] == '$')
	{
		i++;
		j = 0;
		while (value[j])
		{
			final[k] = value[j];
			j++;
			k++;
		}
	}
	while (ft_isalnum(s[i]) || s[i] == '_')
		i++;
	while (s[i])
	{
		final[k] = s[i];
		i++;
		k++;
	}
	final[k] = '\0';
	return (final);
}

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

char	*get_value_vars(t_command cmd)
{
	char	*new_line;
	char	*var;
	char	*value;
	unsigned int		i;
	unsigned int		j;
	
	i = 0;
	j = 0;
	new_line = ft_strdup(cmd.cmd_line);
	while (cmd.cmd_line[i])
	{
		if (cmd.cmd_line[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(cmd.cmd_line[i]) || cmd.cmd_line[i] == '_')
				i++;
			var = get_var(cmd.cmd_line, j, i);
			value = getenv(var);
			if (!value)
				new_line = replace_var_by_nothing(new_line, ft_strlen(var));
			else
				new_line = replace_var_by_value(new_line, value, ft_strlen(var));
			free(var);
			var = NULL;
			value = NULL;
		}
		else
			i++;
	}
	printf("newline = %s\n", new_line);
	return (cmd.cmd_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:53:16 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/23 10:35:36 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_and_replace_var(char *token, char *var, char *value)
{
	int		i;
	int		j;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(token[i]) || token[i] == '_' || token[i] == '?')
				i++;
			var = ft_substr(token, j, i - j);
			//if (var == '?')
			//	value = get_ex_code_value();
			value = getenv(var);
			free(var);
			token = replace_var_by_value(token, value, j, i);
			i = ft_strlen(value);
		}
		else
			i++;
	}
	return (token);
}

char	*replace_var_by_value(char *line, char *value, int start, int end)
{
	char	*before_dollar;
	char	*after_var;
	char	*tmp;

	before_dollar = ft_substr(line, 0, start - 1);
	after_var = ft_substr(line, end, ft_strlen(line) - end);
	if (!value)
		line = ft_strjoin(before_dollar, after_var, 0);
	else
	{
		tmp = ft_strjoin(before_dollar, value, 0);
		line = ft_strjoin(tmp, after_var, 0);
		free(tmp);
	}
	free(before_dollar);
	free(after_var);
	return (line);
}

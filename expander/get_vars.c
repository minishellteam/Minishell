/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 09:53:16 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/26 19:07:39 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	get_quote_type(char *token)
{
	char	token_type;

	token_type = 0;
	if (*token == '\"')
		token_type = '\"';
	else if (*token == '\'')
		token_type = '\'';
	else
		return (0);
	return (token_type);
}

static char	*replace_var_by_value(char *line, char *value, int start, int end)
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

static char	*replace_var(char *tok, char *var, int i)
{
	int		j;
	char	*exp_tok;
	char	*value;

	value = NULL;
	while (tok[i])
	{
		if (tok[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(tok[i]) || tok[i] == '_' || tok[i] == '?')
				i++;
			var = ft_substr(tok, j, i - j);
			if (!ft_strncmp(var, "?", ft_strlen(var)))
				value = ft_itoa(g_exit_code);
			else
				value = getenv(var);
			exp_tok = replace_var_by_value(tok, value, j, i);
			free(tok);
			tok = ft_strdup(exp_tok);
			free(exp_tok);
			i = ft_strlen(getenv(var));
			free(var);
		}
		else
			i++;
	}
	return (tok);
}

static char	*replace_unquoted_var(char *new_tok, char *var, char *value)
{
	int	i;
	int	j;

	i = 1;
	j = i;
	while (new_tok[i]
		&& (ft_isalnum(new_tok[i]) || new_tok[i] == '_' || new_tok[i] == '?'))
		i++;
	var = ft_substr(new_tok, j, i - j);
	if (!ft_strncmp(var, "?", ft_strlen(var)))
		value = ft_itoa(g_exit_code);
	else
		value = getenv(var);
	free(var);
	free(new_tok);
	if (!value)
		new_tok = "";
	else
		new_tok = value;
	return (new_tok);
}

char	*get_var(char *token, char *var, char *value, int x)
{
	char	*new_tok;
	int		i;

	new_tok = ft_strdup(token);
	var = NULL;
	value = NULL;
	i = 0;
	if (x == 0)
	{
		new_tok = replace_var(new_tok, var, i);
		free(token);
		token = ft_strdup(new_tok);
		free(new_tok);
	}
	else
	{
		new_tok = replace_unquoted_var(new_tok, var, value);
		free(token);
		if (!ft_strncmp(new_tok, "", ft_strlen(new_tok)))
			token = "";
		else
			token = ft_strdup(new_tok);
	}
	return (token);
}

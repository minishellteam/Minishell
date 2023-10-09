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

static char	*replace_var(char *tok, t_vars *var, int i)
{
	int		j;
	char	*exp_tok;

	while (tok[i])
	{
		if (tok[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(tok[i]) || tok[i] == '_' || tok[i] == '?')
				i++;
			var->var = ft_substr(tok, j, i - j);
			get_value(var);
			exp_tok = replace_var_by_value(tok, var->value, j, i);
			free(tok);
			tok = ft_strdup(exp_tok);
			free(exp_tok);
			i = ft_strlen(var->value);
			free(var->var);
		}
		else
			i++;
	}
	return (tok);
}

static char	*replace_unquoted_var(char *new_tok, t_vars *var)
{
	int	i;
	int	j;

	i = 1;
	j = i;
	if (new_tok[i] == '$' && !new_tok[i + 1])
		var->var = ft_strdup("$");
	else
	{
		while (new_tok[i]
			&& (ft_isalnum(new_tok[i]) || new_tok[i] == '_'
				|| new_tok[i] == '?') && new_tok[i] != '$')
			i++;
		var->var = ft_substr(new_tok, j, i - j);
	}
	get_value(var);
	free(new_tok);
	if (!var->value && !ft_strcmp(var->var, "$"))
		new_tok = "\"\"";
	else if (!var->value)
		new_tok = "";
	else
		new_tok = var->value;
	free(var->var);
	return (new_tok);
}

static char	*handle_unquoted_var(t_vars *var, char *new_tok, char *token)
{
	new_tok = replace_unquoted_var(new_tok, var);
	free(token);
	if (!ft_strcmp(new_tok, ""))
		token = "";
	else
		token = ft_strdup(new_tok);
	free(new_tok);
	return (token);
}

char	*get_var(char *token, t_vars *var, int x)
{
	char	*new_tok;
	int		i;

	new_tok = ft_strdup(token);
	var->var = NULL;
	var->value = NULL;
	var->bool = 0;
	i = 0;
	if (x == 0)
	{
		var->value = NULL;
		new_tok = replace_var(new_tok, var, i);
		free(var->value);
		free(token);
		token = ft_strdup(new_tok);
		free(new_tok);
	}
	else
		token = handle_unquoted_var(var, new_tok, token);
	return (token);
}

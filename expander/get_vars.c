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

static char	*replace_var(char *tok, t_vars *var, int i, int bool)
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
			handle_value(var, bool);
			exp_tok = replace_var_by_value(tok, var->value, j, i);
			free(tok);
			tok = ft_strdup(exp_tok);
			free(exp_tok);
			i = ft_strlen(var->value);
			free(var->var);
			free(var->value);
		}
		else
			i++;
	}
	return (tok);
}

static char	*handle_unquoted_var(t_vars *var, char *new_tok, char *token, int i)
{
	new_tok = replace_var(new_tok, var, i, 1);
	free(token);
	if (!ft_strcmp(new_tok, ""))
		token = "";
	else
		token = ft_strdup(new_tok);
	free(new_tok);
	return (token);
}

char	*get_var(char *token, t_vars *var, int x, int bool)
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
		new_tok = replace_var(new_tok, var, i, bool);
		free(token);
		token = ft_strdup(new_tok);
		free(new_tok);
	}
	else
		token = handle_unquoted_var(var, new_tok, token, i);
	return (token);
}

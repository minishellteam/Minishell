/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:22:28 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/09 23:52:05 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_quoted_token(t_tok *tok, t_vars *var, char q_type)
{
	char	*quoted_token;
	char	*variable;
	char	*value;

	quoted_token = NULL;
	variable = NULL;
	value = NULL;
	tok->tok++;
	var->start = tok->tok;
	while (*(tok->tok) && *(tok->tok) != q_type)
		tok->tok++;
	var->end = tok->tok - 1;
	var->len = var->end - var->start + 1;
	quoted_token = malloc(sizeof(char) * (var->len + 1));
	ft_strlcpy(quoted_token, var->start, var->len + 1);
	if (q_type == '\"')
		quoted_token = search_and_replace_var(quoted_token, variable, value);
	return (quoted_token);
}

static char	*get_non_quoted_tok(t_tok *tok, t_vars *var)
{
	char	*str_tok;
	char	*variable;
	char	*value;

	str_tok = NULL;
	variable = NULL;
	value = NULL;
	if (*(tok->tok) && *(tok->tok) != '\'' && *(tok->tok) != '\"'
		&& !ft_isspace(*(tok->tok)) && !is_special_char(*(tok->tok)))
	{
		var->start = (tok->tok);
		while (*(tok->tok) && *(tok->tok) != '\'' && *(tok->tok) != '\"'
			&& !ft_isspace(*(tok->tok)) && !is_special_char(*(tok->tok)))
			tok->tok++;
		var->end = (tok->tok) - 1;
		var->len = var->end - var->start + 1;
		str_tok = malloc(sizeof(char) * (var->len + 1));
		ft_strlcpy(str_tok, var->start, var->len + 1);
		str_tok = search_and_replace_var(str_tok, variable, value);
	}
	else
		str_tok = "";
	return (str_tok);
}

static char	*expand_token(t_tok *token, t_vars *var)
{
	char	*tmp_tok;
	char	*quoted_tok;
	char	*str_tok;
	char	quote_type;

	str_tok = NULL;
	tmp_tok = get_non_quoted_tok(token, var);
	while (*(token->tok) && !is_special_char(*(token->tok))
		&& !ft_isspace(*(token->tok)))
	{
		quote_type = get_quote_type(token->tok);
		if (!get_quote_type(token->tok))
			return (NULL);
		quoted_tok = get_quoted_token(token, var, quote_type);
		tmp_tok = ft_strjoin(tmp_tok, quoted_tok);
		token->tok++;
		str_tok = get_non_quoted_tok(token, var);
		tmp_tok = ft_strjoin(tmp_tok, str_tok);
	}
	return (tmp_tok);
}

static int	check_if_empty_tok(t_tok *tmp, t_vars *var)
{
	if (tmp->tok && tmp->tok[0] == '\"' && tmp->tok[1] == '$')
	{
		var->start = tmp->tok + 2;
		var->end = var->start;
		while (ft_isalnum(*(var->end)) || *(var->end) == '_'
			|| *(var->end) == '?')
			var->end++;
		if (*(var->end) == '\"' && !*(var->end + 1))
		{
			tmp->tok = get_vars(tmp);
			if (!ft_strncmp(tmp->tok, "\"\"", ft_strlen(tmp->tok)))
			{
				tmp->type = "EMPTY";
				tmp = tmp->next;
				return (1);
			}
		}
	}
	else if (!ft_strncmp(tmp->tok, "$", ft_strlen(tmp->tok)))
	{
		tmp->type = "EMPTY";
		return (1);
	}
	return (0);
}

int	handle_quotes(t_vars *var)
{
	t_tok	*tmp;

	tmp = var->toks;
	var->start = NULL;
	var->end = NULL;
	var->len = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "STRING", ft_strlen(tmp->type)))
		{
			if (check_if_empty_tok(tmp, var) == 1)
				break ;
			tmp->tok = expand_token(tmp, var);
			if (!ft_strncmp(tmp->tok, "", ft_strlen(tmp->tok)))
				tmp->type = "SKIP";
		}
		tmp = tmp->next;
	}
	return (0);
}

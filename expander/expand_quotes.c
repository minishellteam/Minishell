/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 09:22:28 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/07/05 14:46:40 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_quoted_token(t_tok *tok, char *start, char *end, char q_type)
{
	char	*quoted_token;
	char	*var;
	char	*value;
	int		len;

	quoted_token = NULL;
	var = NULL;
	value = NULL;
	tok->tok++;
	start = tok->tok;
	while (*(tok->tok) && *(tok->tok) != q_type)
		tok->tok++;
	end = tok->tok - 1;
	len = end - start + 1;
	quoted_token = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(quoted_token, start, len + 1);
	if (q_type == '\"')
		quoted_token = search_and_replace_var(quoted_token, var, value);
	return (quoted_token);
}

static char	*get_non_quoted_tok(t_tok *tok, char *start, char *end, int len)
{
	char	*str_tok;
	char	*var;
	char	*value;

	str_tok = NULL;
	var = NULL;
	value = NULL;
	if (*(tok->tok) && *(tok->tok) != '\'' && *(tok->tok) != '\"'
		&& !ft_isspace(*(tok->tok)) && !is_special_char(*(tok->tok)))
	{
		start = (tok->tok);
		while (*(tok->tok) && *(tok->tok) != '\'' && *(tok->tok) != '\"'
			&& !ft_isspace(*(tok->tok)) && !is_special_char(*(tok->tok)))
			tok->tok++;
		end = (tok->tok) - 1;
		len = end - start + 1;
		str_tok = malloc(sizeof(char) * (len + 1));
		ft_strlcpy(str_tok, start, len + 1);
		str_tok = search_and_replace_var(str_tok, var, value);
	}
	else
		str_tok = "";
	return (str_tok);
}

static char	*expand_token(t_tok *token, char *start, char *end, int token_len)
{
	char	*tmp_tok;
	char	*quoted_tok;
	char	*str_tok;
	char	quote_type;

	str_tok = NULL;
	tmp_tok = get_non_quoted_tok(token, start, end, token_len);
	while (*(token->tok) && !is_special_char(*(token->tok))
		&& !ft_isspace(*(token->tok)))
	{
		quote_type = get_quote_type(token->tok);
		if (!get_quote_type(token->tok))
			return (NULL);
		quoted_tok = get_quoted_token(token, start, end, quote_type);
		tmp_tok = ft_strjoin(tmp_tok, quoted_tok);
		token->tok++;
		str_tok = get_non_quoted_tok(token, start, end, token_len);
		tmp_tok = ft_strjoin(tmp_tok, str_tok);
	}
	return (tmp_tok);
}

static int	check_if_empty_tok(t_tok *tmp, char *start, char *end)
{
	if (tmp->tok && tmp->tok[0] == '\"' && tmp->tok[1] == '$')
	{
		start = tmp->tok + 2;
		end = start;
		while (ft_isalnum(*end) || *end == '_' || *end == '?')
			end++;
		if (*end == '\"' && !*(end + 1))
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

int	handle_quotes(void)
{
	t_tok	*tmp;
	char	*start;
	char	*end;
	int		token_len;

	tmp = g_sh.toks;
	start = NULL;
	end = NULL;
	token_len = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "STRING", ft_strlen(tmp->type)))
		{
			if (check_if_empty_tok(tmp, start, end) == 1)
				break ;
			tmp->tok = expand_token(tmp, start, end, token_len);
			if (!ft_strncmp(tmp->tok, "", ft_strlen(tmp->tok)))
				tmp->type = "SKIP";
		}
		tmp = tmp->next;
	}
	// printf("after expander:\n");
	// print_list(g_sh.toks, 0);
	// print_list(g_sh.toks, 1);
	return (0);
}

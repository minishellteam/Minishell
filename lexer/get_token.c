/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/21 12:40:13 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_special_tok(t_vars *var)
{
	char	special_tok[2];
	char	*token;

	token = get_double_chevrons_token(var);
	if (token)
		return (token);
	var->len = 1;
	special_tok[0] = *(var->line);
	special_tok[1] = '\0';
	if (is_forbidden_char(special_tok[0]))
	{
		get_error_message(special_tok, 0);
		return (NULL);
	}
	if (check_question_mark(var->line, special_tok))
		return (NULL);
	token = malloc(sizeof(char) * (var->len + 1));
	ft_strlcpy(token, special_tok, var->len + 1);
	var->line++;
	return (token);
}

static int	handle_quote_case(t_vars *var, char **token)
{
	char	*quote;

	quote = var->line;
	if ((*(var->line) == '\"' && *(var->line + 1) == '\"')
		|| (*(var->line) == '\'' && *(var->line + 1) == '\''))
	{
		var->line += 2;
		*token = "";
		return (1);
	}
	if (check_quote_in_str(var, var->start, var->end))
		return (1);
	var->line++;
	while (*(var->line) != *quote)
		var->line++;
	return (0);
}

static char	*get_string_tok(t_vars *var)
{
	char		*token;

	token = NULL;
	var->start = var->line;
	var->x = 0;
	while (*(var->line) && !ft_isspace(*(var->line))
		&& !is_special_char(*(var->line)))
	{
		if (*(var->line) == '\"' || *(var->line) == '\'')
			if (handle_quote_case(var, &token))
				return (token);
		var->line++;
	}
	var->end = var->line - 1;
	var->len = var->end - var->start + 1;
	token = malloc(sizeof(char) * (var->len + 1));
	ft_strlcpy(token, var->start, var->len + 1);
	return (token);
}

static char	*get_token(t_vars *var)
{
	char	*token;

	token = NULL;
	var->len = 0;
	var->end = NULL;
	while (ft_isspace(*(var->line)))
		var->line++;
	var->start = var->line;
	if (is_special_char(*(var->line)))
		token = get_special_tok(var);
	else if (*var->line == '$' && *(var->line + 1) == '?')
		token = get_ex_code_token(var);
	else
		token = get_string_tok(var);
	return (token);
}

int	tokenize_line(char *line, t_vars *var)
{
	var->line = line;
	if (*(var->line) == '?')
	{
		get_error_message("?", 0);
		return (1);
	}
	while (*(var->line))
	{
		var->start = line;
		var->token = get_token(var);
		if (!var->token)
			return (1);
		var->tok = ft_lst_new(var->token);
		ft_lst_add_back(&(var->toks), var->tok);
		while (*(var->line) && ft_isspace(*(var->line)))
			var->line++;
	}
	var->toks = get_token_type(var->toks);
	if (parse_tokens(var))
		return (1);
	get_limiter(var->toks);
	check_limiter(var);
	handle_quotes(var);
	get_files(var->toks);
	//printf("tokens= \n");
	//print_list(var->toks, 0);
	//print_list(var->toks, 1);
	return (0);
}

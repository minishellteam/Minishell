/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/12 17:15:36 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char token)
{
	if (token == '|' || token == '<' || token == '>')
		return (1);
	return (0);
}

char	*get_token(char *token_start)
{
	char	*token;
	char	*token_end;
	int		token_len;
	char	special_tok[2];

	token = NULL;
	token_len = 0;
	if (*g_sh.line == ' ')
	{
		while (*g_sh.line == ' ')
			g_sh.line++;
		token_start = g_sh.line;
	}
	if (is_special_char(*g_sh.line))
	{
		token_len = 1;
		special_tok[0] = *g_sh.line;
		special_tok[1] = '\0';
		token = malloc(sizeof(char) * (token_len + 1));
		ft_strlcpy(token, special_tok, token_len + 1);
	}
	else
	{
		while (*g_sh.line && !is_special_char(*g_sh.line) && *g_sh.line != ' ')
			g_sh.line++;
		token_end = g_sh.line;
		token_len = token_end - token_start;
		token = malloc(sizeof(char) * (token_len + 1));
		ft_strlcpy(token, token_start, token_len + 1);
	}
	return (token);
}

void	tokenize_line()
{
	t_tok	*tokens;
	t_tok	*tok;
	char	*token;
	char	*token_start;

	tokens = NULL;
	while (*g_sh.line)
	{
		token_start = g_sh.line;
		token = get_token(token_start);
		printf("token = %s\n", token);
		tok = ft_lst_new(token);
		ft_lst_add_back(&tokens, tok);
		g_sh.line++;
	}
	print_list(tokens);
}

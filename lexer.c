/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:46:12 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/11 16:58:16 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_line(t_data g_sh)
{
	t_tok	*tokens;
	t_tok	*tmp;
	char	*limiter;
	char	*token;
	char	*token_start;
	char	*token_end;
	int		token_len;

	limiter = " |<>\n";
	while (*g_sh.line)
	{
		while (*g_sh.line && !ft_strchr(limiter, *g_sh.line))
			g_sh.line++;
		if (!*g_sh.line)
			break ;
		token_start = g_sh.line;
		while (*g_sh.line && ft_strchr(limiter, *g_sh.line))
			g_sh.line++;
	}
	token_end = g_sh.line - 1;
	token_len = token_end - token_start + 1;
	token = malloc(sizeof(char) * token_len + 1);
	ft_strncpy(token, token_start, token_len);
	tokens = ft_lst_new(token);
}

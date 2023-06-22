/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:51:03 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/22 09:43:33 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	get_token_type(void)
// {
// 	enum e_toktype token_type;

// 	token_type = STRING;
// 	while (g_sh.toks != NULL)
// 	{
// 		if (!ft_strncmp(g_sh.toks->tok, "", ft_strlen(g_sh.toks->tok)))
// 			token_type = EMPTY;
// 		else if (!ft_strncmp(g_sh.toks->tok, "|", ft_strlen(g_sh.toks->tok)))
// 			token_type = PIPE;
// 		else if (!ft_strncmp(g_sh.toks->tok, ">", ft_strlen(g_sh.toks->tok)))
// 			token_type = GREATER;
// 		else if (!ft_strncmp(g_sh.toks->tok, ">>", ft_strlen(g_sh.toks->tok)))
// 			token_type = DOUBLE_GREATER;
// 		else if (!ft_strncmp(g_sh.toks->tok, "<", ft_strlen(g_sh.toks->tok)))
// 			token_type = LESSER;
// 		else if (!ft_strncmp(g_sh.toks->tok, "<<", ft_strlen(g_sh.toks->tok)))
// 			token_type = DOUBLE_LESSER;
// 		else
// 			token_type = STRING;
// 		g_sh.toks = g_sh.toks->next;
// 	}
// }

t_tok	*get_token_type(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->tok, "", ft_strlen(tmp->tok)))
			tmp->type = "EMPTY";
		else if (!ft_strncmp(tmp->tok, "|", ft_strlen(tmp->tok)))
			tmp->type = "PIPE";
		else if (!ft_strncmp(tmp->tok, ">", ft_strlen(tmp->tok)))
			tmp->type = "GREATER";
		else if (!ft_strncmp(tmp->tok, ">>", ft_strlen(tmp->tok)))
			tmp->type = "DOUBLE_GREATER";
		else if (!ft_strncmp(tmp->tok, "<", ft_strlen(tmp->tok)))
			tmp->type = "LESSER";
		else if (!ft_strncmp(tmp->tok, "<<", ft_strlen(tmp->tok)))
			tmp->type = "DOUBLE_LESSER";
		else
			tmp->type = "STRING";
		tmp = tmp->next;
	}
	return (toks);
}

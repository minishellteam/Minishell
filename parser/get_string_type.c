/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:27:08 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/07/05 14:07:37 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_files(void)
{
	t_tok	*tmp;

	tmp = g_sh.toks;
	while (tmp && tmp->next)
	{
		if (is_chevron(tmp->type, 1))
			tmp->next->type = "FILE";
		tmp = tmp->next;
	}
}

// void	remove_token(t_tok *tmp)
// {
// 	t_tok	*current;
// 	t_tok	*new_next;

// 	current = g_sh.toks;
// 	new_next = NULL;
// 	if (current == tmp)
// 		g_sh.toks = g_sh.toks->next;
// 	while (current && current->next)
// 	{
// 		if (current->next == tmp)
// 		{
// 			if (current->next->next)
// 			{
// 				new_next = current->next->next;
// 				current->next = new_next;
// 			}
// 			else
// 				current->next = NULL;
// 		}
// 		current = current->next;
// 	}
// }

// void	remove_empty_tok(void)
// {
// 	t_tok	*tmp;

// 	tmp = g_sh.toks;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->type, "EMPTY", ft_strlen(tmp->type)))
// 			remove_token(tmp);
// 		tmp = tmp->next;
// 	}
// }

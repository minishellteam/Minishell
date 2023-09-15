/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:27:08 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/15 12:03:35 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_files(t_tok *toks)
{
	t_tok	*tmp;

	tmp = toks;
	while (tmp && tmp->next)
	{
		if (is_chevron(tmp->type, 1))
		{
			if (!ft_strcmp(tmp->type, "D_LESSER"))
				tmp->next->type = "LIMITER";
			else
				tmp->next->type = "FILE";
		}
		tmp = tmp->next;
	}
}

// void	remove_token(t_tok *toks, t_tok *tmp)
// {
// 	t_tok	*current;
// 	t_tok	*new_next;

// 	current = toks;
// 	new_next = NULL;
// 	if (current == tmp)
// 		toks = toks->next;
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

// 	tmp = toks;
// 	while (tmp)
// 	{
// 		if (!ft_strcmp(tmp->type, "EMPTY"))
// 			remove_token(tmp);
// 		tmp = tmp->next;
// 	}
// }

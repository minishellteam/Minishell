/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:27:08 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/22 17:08:46 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_options(void)
{
	t_tok	*tmp;

	tmp = g_sh.toks;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "STRING", ft_strlen(tmp->type)))
		{
			if (!ft_strncmp(tmp->tok, "-", 1))
				tmp->type = "OPTION";
		}
		tmp = tmp->next;
	}
}

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

void	get_commands(void)
{
	t_tok	*tmp;
	t_tok	*tmp2;

	tmp = g_sh.toks;
	tmp2 = tmp;
	while (tmp && tmp->next)
	{
		while (tmp2 && ft_strncmp(tmp2->type, "PIPE", ft_strlen(tmp2->type)))
		{
			if (!ft_strncmp(tmp2->type, "STRING", ft_strlen(tmp2->type)))
			{
				tmp2->type = "COMMAND";
				while (tmp2 && tmp2->next
					&& ft_strncmp(tmp2->type, "PIPE", ft_strlen(tmp2->type)))
					tmp2 = tmp2->next;
				if (!tmp2 || !tmp2->next)
					return ;
				tmp2 = tmp2->next;
				tmp = tmp2;
				break ;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	get_arguments(void)
{
	t_tok	*tmp;

	tmp = g_sh.toks;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "STRING", ft_strlen(tmp->type)))
			tmp->type = "ARGUMENT";
		tmp = tmp->next;
	}
}

void	remove_token(t_tok *tmp)
{
	t_tok	*current;
	t_tok	*new_next;

	current = g_sh.toks;
	new_next = NULL;
	if (current == tmp)
		g_sh.toks = g_sh.toks->next;
	while (current && current->next)
	{
		if (current->next == tmp)
		{
			if (current->next->next)
			{
				new_next = current->next->next;
				current->next = new_next;
			}
			else
				current->next = NULL;
		}
		current = current->next;
	}
}

void	remove_empty_tok(void)
{
	t_tok	*tmp;

	tmp = g_sh.toks;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "EMPTY", ft_strlen(tmp->type)))
			remove_token(tmp);
		tmp = tmp->next;
	}
}

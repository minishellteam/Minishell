/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 16:19:27 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/15 12:03:06 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tok	*ft_lst_new(char *token)
{
	t_tok	*new_lst;

	new_lst = malloc(sizeof(t_tok));
	if (!new_lst)
		return (NULL);
	new_lst->tok = token;
	new_lst->next = NULL;
	new_lst->prev = NULL;
	return (new_lst);
}

void	ft_lst_add_back(t_tok **lst, t_tok *new)
{
	t_tok	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	print_list(t_tok *token, int x)
{
	t_tok	*tmp;

	tmp = token;
	if (x == 0)
	{
		while (tmp != NULL)
		{
			printf("%s\n", tmp->tok);
			tmp = tmp->next;
		}
	}
	else if (x == 1)
	{
		while (tmp != NULL)
		{
			printf("%s\n", tmp->type);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp != NULL)
		{
			printf("%s\n", tmp->prev->type);
			tmp = tmp->next;
		}
	}
}

t_tok	*ft_lst_last(t_tok *lst)
{
	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (lst);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lst_size(t_tok *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	i = 0;
	while (lst->next != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i + 1);
}

void	free_list(t_tok **lst, int x)
{
	t_tok	*tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (x == 0 && ft_strcmp(tmp->tok, ""))
			free(tmp->tok);
		free(tmp);
	}
	free(*lst);
}

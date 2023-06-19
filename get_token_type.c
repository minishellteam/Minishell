/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:51:03 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/19 17:05:05 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_token_type(void)
{
	t_tok	*tmp;

	tmp = g_sh.tokens;
	while (tmp != NULL)
	{
		if (!ft_strncmp(tmp->token, "|", ft_strlen(tmp->token)))
			tmp->type = "PIPE";
		else if (!ft_strncmp(tmp->token, ">", ft_strlen(tmp->token)))
			tmp->type = "GREATER";
		else if (!ft_strncmp(tmp->token, ">>", ft_strlen(tmp->token)))
			tmp->type = "DOUBLE_GREATER";
		else if (!ft_strncmp(tmp->token, "<", ft_strlen(tmp->token)))
			tmp->type = "LESSER";
		else if (!ft_strncmp(tmp->token, "<<", ft_strlen(tmp->token)))
			tmp->type = "DOUBLE_LESSER";
		else
			tmp->type = "STRING";
		tmp = tmp->next;
	}
	t_tok *tmp2 = g_sh.tokens;
	while (tmp2 != NULL)
	{
		printf("types = %s\n", tmp2->type);
		tmp2 = tmp2->next;
	}
}

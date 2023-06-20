/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:06:06 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/20 15:30:18 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_pipeline(void)
{
	t_tok	*tmp;
	int		pipe_nb;
	
	tmp = g_sh.toks;
	pipe_nb = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type))) 
			pipe_nb++;
		tmp = tmp->next;
	}
	printf("pipe_nb = %d\n", pipe_nb);
	
}

void	parse_tokens(void)
{
	int	nb_of_toks;

	nb_of_toks = ft_lst_size(g_sh.toks);
	parse_pipeline();
}
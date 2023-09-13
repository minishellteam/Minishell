/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/13 16:36:43 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	free_exit(void)
// {
// 	// if (sh->export->env || sh->export->exp)
// 	// 	free_tab();
// 	exit(EXIT_SUCCESS);
// }

static void	arg_error(t_data *sh)
{
	int		i;

	i = -1;
	while (sh->cmds[1][++i])
	{
		if (!ft_isdigit(sh->cmds[1][i]))
		{
			get_error_message(sh->cmds[1], 5);
			// METTRE LA GLOBALE A 255
			return ;
		}
	}
	// FAIRE MODULO DE CMD[1] de 256
}

void	built_exit(t_data *sh)
{
	printf("exit\n");
	// if (array_size(sh->cmds) <= 3)
	// 	free_exit();
	if (array_size(sh->cmds) == 2)
		exit(EXIT_SUCCESS);
	if (array_size(sh->cmds) == 3)
		arg_error(sh);
	else if (array_size(sh->cmds) > 3)
		get_error_message(NULL, 6);
		// METTRE LA GLOBALE A 1
}

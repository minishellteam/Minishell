/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:22:52 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/03 14:54:54 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_echo(t_data *sh, int bool)
{
	sh->j--;
	while (sh->cmds[++sh->j])
	{
		if (!ft_strcmp(sh->cmds[sh->j], "\"\""))
			printf(" ");
		else
			printf("%s", sh->cmds[sh->j]);
		if (sh->cmds[sh->j + 1])
			printf(" ");
	}
	if (bool == 0)
		printf("\n");
}

static int	check_n(t_data *sh)
{
	int	bool;

	sh->j = 0;
	bool = 0;
	while (sh->cmds[++sh->j])
	{
		if (sh->cmds[sh->j][0] == '-' && ft_strlen(sh->cmds[sh->j]) > 1)
		{
			sh->i = 0;
			while (sh->cmds[sh->j][++sh->i])
				if (sh->cmds[sh->j][sh->i] != 'n')
					return (bool);
			bool = 1;
		}
		else
			return (bool);
	}
	return (bool);
}

void	built_echo(t_data *sh)
{
	int	bool;

	sh->j = 0;
	if (check_n(sh) == 1)
		bool = 1;
	else
		bool = 0;
	print_echo(sh, bool);
	bool = -1;
}

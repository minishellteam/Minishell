/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:22:52 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/29 08:33:17 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_echo(int bool)
{
	g_sh.j--;
	while (g_sh.echo[++g_sh.j])
	{
		printf("%s", g_sh.echo[g_sh.j]);
		if (g_sh.echo[g_sh.j + 1])
			printf(" ");
	}
	if (bool == 0)
		printf("\n");
}

static int	check_n(void)
{
	int	bool;

	g_sh.j = 0;
	bool = 0;
	while (g_sh.echo[++g_sh.j])
	{
		if (g_sh.echo[g_sh.j][0] == '-' && ft_strlen(g_sh.echo[g_sh.j]) > 1)
		{
			g_sh.i = 0;
			while (g_sh.echo[g_sh.j][++g_sh.i])
				if (g_sh.echo[g_sh.j][g_sh.i] != 'n')
					return (bool);
			bool = 1;
		}
		else
			return (bool);
	}
	return (bool);
}

void	built_echo()
{
	int	bool;

	g_sh.j = 0;
	if (!ft_strncmp(g_sh.cmds[g_sh.j], "echo", 4) \
		&& g_sh.cmds[g_sh.j][4] != ' ')
	{
		printf("pass\n");
		return ;
	}
	g_sh.echo = ft_split(g_sh.cmds[g_sh.j], ' ');
	if (check_n() == 1)
		bool = 1;
	else
		bool = 0;
	print_echo(bool);
	bool = -1;
	while (g_sh.echo[++bool])
		free(g_sh.echo[bool]);
}

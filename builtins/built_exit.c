/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/07/01 11:06:47 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_exit(void)
{
	if (g_sh.export->env || g_sh.export->exp)
		free_tab();
	system("leaks minishell");
	exit(EXIT_SUCCESS);
}

static void	arg_error(void)
{
	char	*new;
	int		i;
	int		j;

	i = 4;
	while (g_sh.line[++i])
	{
		if (!ft_isdigit(g_sh.line[i]))
		{
			new = malloc(sizeof(char) * (ft_strlen(g_sh.line) - 3));
			i = 4;
			j = -1;
			while (g_sh.line[++i] && g_sh.line[i] != ' ')
				new[++j] = g_sh.line[i];
			new[j + 1] = '\0';
			printf("minishell: exit: %s: numeric argument required\n",
				new);
			free(new);
			new = NULL;
			return ;
		}
	}
}

void	built_exit(void)
{
	int	i;

	i = 4;
	g_sh.line = ft_strtrim(g_sh.line, " ");
	if (!ft_strncmp(g_sh.line, "exit", 4) && !ft_strchr(g_sh.line, '|'))
	{
		if (ft_strlen(g_sh.line) > 4 && g_sh.line[4] != ' ')
			return ;
		printf("exit\n");
		if (ft_strlen(g_sh.line) > 4)
			arg_error();
		if (ft_strlen(g_sh.line) > 4 && g_sh.line[5] == '1')
			exit(EXIT_FAILURE);
		else if (ft_strlen(g_sh.line) > 4 && g_sh.line[5] == '0')
			exit(EXIT_SUCCESS);
		free_exit();
	}
}

void	ft_builts()
{
	g_sh.cmds = ft_split(g_sh.line, '|');
	built_exit();
	built_echo();
	built_pwd();
	built_cd();
	built_export();
	built_env();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:39:01 by ykifadji          #+#    #+#             */
/*   Updated: 2023/07/05 11:55:46 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(void)
{
	int	j;

	j = 0;
	while (g_sh.export->env[j] || g_sh.export->exp[j])
	{
		if (g_sh.export->env[j])
			free(g_sh.export->env[j]);
		if (g_sh.export->exp[j])
			free(g_sh.export->exp[j]);
		j++;
	}
	free(g_sh.export->env);
	free(g_sh.export->exp);
}

void	built_pwd(void)
{
	char	buffer[BUFF_SIZE];

	if (!ft_strncmp(g_sh.cmds[0], "pwd", 3) && ft_strlen(g_sh.cmds[0]) == 3)
	{
		if (getcwd(buffer, BUFF_SIZE))
			printf("%s\n", buffer);
		else
			handle_error("minishell: ", 1);
	}
}

void	built_cd(void)
{
	char	**tmp;

	if (!ft_strncmp(g_sh.cmds[0], "cd", 2))
	{
		tmp = ft_split(g_sh.line, ' ');
		if (chdir(tmp[1]) == -1)
			handle_error("minishell$ ", 1);
	}
}

void	built_env(void)
{
	int	i;

	i = -1;
	if (!ft_strncmp(g_sh.cmds[0], "env", 3))
	{
		while (g_sh.env[++i])
			printf("%s\n", g_sh.env[i]);
	}
}

void	my_env(void)
{
	g_sh.j = -1;
	g_sh.myenv = malloc(sizeof(char *) * len_env(g_sh.env));
	while (g_sh.env[++g_sh.j])
	{
		g_sh.myenv[g_sh.j] = malloc(sizeof(char) \
			* (ft_strlen(g_sh.env[g_sh.j]) + 1));
		ft_strlcpy(g_sh.myenv[g_sh.j], g_sh.env[g_sh.j], \
			(ft_strlen(g_sh.env[g_sh.j]) + 1));
	}
	g_sh.env[g_sh.j + 1] = NULL;
}

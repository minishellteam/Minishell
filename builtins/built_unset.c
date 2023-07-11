/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/07/11 12:07:11 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env(char **tmp)
{
	g_sh.j = -1;
	g_sh.myenv = malloc(sizeof(char *) * len_env(tmp));
	while (tmp[++g_sh.j])
	{
		g_sh.myenv[g_sh.j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[g_sh.j]) + 1));
		ft_strlcpy(g_sh.myenv[g_sh.j], tmp[g_sh.j], \
			(ft_strlen(tmp[g_sh.j]) + 1));
		//free(tmp[g_sh.j]);
	}
	//free(tmp);
	g_sh.myenv[g_sh.j + 1] = NULL;
}
// PROBLEME SUR UNSET CA SUPPRIME TROP DE VAR

void	built_unset(void)
{
	char	**tmp;
	char	**arg;

	if (!ft_strncmp(g_sh.line, "unset", 5))
	{
		g_sh.j = -1;
		tmp = malloc(sizeof(char *) * len_env(g_sh.myenv));
		arg = ft_split(g_sh.cmds[0], ' ');
		while (g_sh.myenv[++g_sh.j])
		{
			if (!ft_strncmp(arg[1], g_sh.myenv[g_sh.j], ft_strlen(arg[1])))
			{
				free(g_sh.myenv[g_sh.j]);
				g_sh.j++;
			}
			tmp[g_sh.j] = malloc(sizeof(char) \
				* (ft_strlen(g_sh.myenv[g_sh.j]) + 1));
			ft_strlcpy(tmp[g_sh.j], g_sh.myenv[g_sh.j], \
				(ft_strlen(g_sh.myenv[g_sh.j]) + 1));
			free(g_sh.myenv[g_sh.j]);
		}
		tmp[g_sh.j + 1] = NULL;
		free(g_sh.myenv);
		update_env(tmp);
	}
}

// void	export_var(char *var)
// {
// 	char	**tmp;

// 	g_sh.j = -1;
// 	tmp = malloc(sizeof(char *) * (len_env(g_sh.myenv) + 2));
// 	while (g_sh.myenv[++g_sh.j])
// 	{
// 		tmp[g_sh.j] = malloc(sizeof(char) \
// 			* (ft_strlen(g_sh.myenv[g_sh.j]) + 1));
// 		ft_strlcpy(tmp[g_sh.j], g_sh.myenv[g_sh.j], \
// 			(ft_strlen(g_sh.myenv[g_sh.j]) + 1));
// 		free(g_sh.myenv[g_sh.j]);
// 	}
// 	ft_strlcpy(tmp[g_sh.j + 1], var, ft_strlen(var));
// 	tmp[g_sh.j + 2] = NULL;
// 	update_env(tmp);
// }

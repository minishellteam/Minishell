/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/07/07 16:51:14 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_unset(void)
{
	char	**tmp;
	char	**arg;
	int		i;

	g_sh.j = -1;
	tmp = malloc(sizeof(char *) * len_env(g_sh.myenv));
	arg = ft_split(g_sh.cmds[0], ' ');
	while (g_sh.myenv[++g_sh.j])
	{
		if (!ft_strncmp(arg[1], g_sh.myenv[g_sh.j], ft_strlen(arg[1])))
			g_sh.j++;
		tmp[g_sh.j] = malloc(sizeof(char) \
			* (ft_strlen(g_sh.myenv[g_sh.j]) + 1));
		ft_strlcpy(g_sh.export->env[g_sh.j], g_sh.myenv[g_sh.j], \
			(ft_strlen(g_sh.myenv[g_sh.j]) + 1));
	}
// free myenv
// malloc myenv
}

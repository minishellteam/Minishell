/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:36:49 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/24 08:36:48 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cpy_env(void)
{
	g_sh.j = -1;
	while (g_sh.env[++g_sh.j])
	{
		g_sh.export->env[g_sh.j] = malloc(sizeof(char) \
			* (ft_strlen(g_sh.env[g_sh.j]) + 1));
		ft_strlcpy(g_sh.export->env[g_sh.j], g_sh.env[g_sh.j], \
			(ft_strlen(g_sh.env[g_sh.j]) + 1));
	}
	g_sh.env[g_sh.j + 1] = NULL;
}

static void	search_min(t_export *export, int i)
{
	int	min;
	int	index;

	min = export->env[0][0];
	index = 0;
	export->j = 0;
	while (export->env[++export->j])
	{
		if (export->env[export->j][0] < min)
		{
			min = export->env[export->j][0];
			index = export->j;
		}
	}
	export->j = index;
	export->exp[i] = malloc(sizeof(char) * (ft_strlen(export->env[export->j]) + 3));
}

static void	cpy_export(t_export *export, int j)
{
	int	i;
	int	k;

	i = -1;
	k = -1;
	while (export->env[export->j][++i])
	{
		if (export->env[export->j][i] == '=')
		{
			export->exp[j][k] = '=';
			export->exp[j][k + 1] = '"';
			k += 1;
			i++;
		}
		export->exp[j][++k] = export->env[export->j][i];
	}
	export->exp[j][k + 1] = '"';
	export->exp[j][k + 2] = '\0';
}

static int	len_env(void)
{
	int	len;

	len = 0;
	while (g_sh.env[len])
		len++;
	return (len + 1);
}

void	built_export(void)
{
	int	i;
	char	*prefix;

	if (!ft_strncmp(g_sh.cmds[0], "export", 6) && ft_strlen(g_sh.cmds[0]) == 6)
	{
		i = -1;
		prefix = "declare -x ";
		g_sh.export = malloc(sizeof(t_export));
		g_sh.export->exp = malloc(sizeof(char *) * len_env());
		g_sh.export->env = malloc(sizeof(char *) * len_env());
		cpy_env();
		while (g_sh.export->env[++i])
		{
			search_min(g_sh.export, i);
			cpy_export(g_sh.export, i);
			g_sh.export->exp[i] = ft_strjoin(prefix, g_sh.export->exp[i], 2);
			g_sh.export->env[g_sh.export->j][0] = 126;
			printf("%s \n", g_sh.export->exp[i]);
		}
		free_tab();
	}
}

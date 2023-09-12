/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:36:49 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/12 10:56:09 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cpy_env(t_data *sh)
{
	sh->j = -1;
	while (sh->myenv[++sh->j])
	{
		sh->export->env[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(sh->export->env[sh->j], sh->myenv[sh->j], \
			(ft_strlen(sh->myenv[sh->j]) + 1));
	}
	sh->export->env[sh->j + 1] = NULL;
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

int	len_env(char **env)
{
	int	len;

	len = 0;
	while (env[len])
		len++;
	return (len + 1);
}

void	built_export(t_data *sh)
{
	int		i;
	char	*prefix;
	//char	**tmp;

	if (!ft_strncmp(sh->cmds[0], "export", 6) && ft_strlen(sh->cmds[0]) == 6)
	{
		i = -1;
		// tmp = ft_split(sh->cmds[0], ' ');
		// export_var(tmp[1]);
		prefix = "declare -x ";
		sh->export = malloc(sizeof(t_export));
		sh->export->exp = malloc(sizeof(char *) * len_env(sh->myenv));
		sh->export->env = malloc(sizeof(char *) * len_env(sh->myenv));
		cpy_env(sh);
		while (sh->export->env[++i])
		{
			search_min(sh->export, i);
			cpy_export(sh->export, i);
			sh->export->exp[i] = ft_strjoin(prefix, sh->export->exp[i], 2);
			sh->export->env[sh->export->j][0] = 126;
			printf("%s \n", sh->export->exp[i]);
		}
		//free_tab();
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:36:49 by ykifadji          #+#    #+#             */
/*   Updated: 2023/06/23 07:44:18 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cpy_env(t_data *cmd)
{
	cmd->j = -1;
	while (cmd->env[++cmd->j])
	{
		cmd->export->env[cmd->j] = malloc(sizeof(char) \
			* (ft_strlen(cmd->env[cmd->j]) + 1));
		ft_strlcpy(cmd->export->env[cmd->j], cmd->env[cmd->j], \
			(ft_strlen(cmd->env[cmd->j]) + 1));
	}
	cmd->env[cmd->j + 1] = NULL;
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

size_t	len_env(t_data *cmd)
{
	size_t	len;

	len = 0;
	while (cmd->env[len])
		len++;
	return (len + 1);
}

void	built_export(t_data *cmd)
{
	int	i;
	char	*prefix;

	if (!ft_strncmp(cmd->cmds[0], "export", 6) && ft_strlen(cmd->cmds[0]) == 6)
	{
		i = -1;
		prefix = "declare -x ";
		cmd->export->env = malloc(sizeof(char *) * (unsigned long)len_env);
		cmd->export->exp = malloc(sizeof(char *) * (unsigned long)len_env);
		cpy_env(cmd);
		while (cmd->export->env[++i])
		{
			search_min(cmd->export, i);
			cpy_export(cmd->export, i);
			cmd->export->exp[i] = ft_strjoin(prefix, cmd->export->exp[i], 2);
			cmd->export->env[cmd->export->j][0] = 126;
			printf("%s \n", cmd->export->exp[i]);
		}
		free_tab(cmd);
	}
}

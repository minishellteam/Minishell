/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:18:56 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/06 12:58:27 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exp_env(t_data *sh)
{
	sh->j = -1;
	sh->expenv = malloc(sizeof(char *) * array_size(sh->myenv));
	while (sh->myenv[++sh->j])
	{
		sh->expenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(sh->expenv[sh->j], sh->myenv[sh->j], \
			(ft_strlen(sh->myenv[sh->j]) + 1));
	}
	sh->expenv[sh->j] = NULL;
}

char	*check_var(char *var)
{
	int		i;
	char	*final;
	
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	final = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (var[++i] && var[i] != '=')
		final[i] = var[i];
	final[i] = '\0';
	return (final);
}

static void	update_envs(t_data *sh, char **tmp, int bool)
{
	sh->j = -1;
	sh->expenv = malloc(sizeof(char *) * array_size(tmp));
	if (bool == 1)
		sh->myenv = malloc(sizeof(char *) * array_size(tmp));
	while (tmp[++sh->j])
	{
		if (bool == 1 && ft_strchr(tmp[sh->j], '='))
		{
			sh->myenv[sh->j] = malloc(sizeof(char) \
				* (ft_strlen(tmp[sh->j]) + 1));
			ft_strlcpy(sh->myenv[sh->j], tmp[sh->j], \
				(ft_strlen(tmp[sh->j]) + 1));
		}
		sh->expenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->expenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	if (bool == 1)
		sh->myenv[sh->j] = NULL;
	sh->expenv[sh->j] = NULL;
}

static	int	check_free(t_data *sh)
{
	int	i;
	int	bool;

	i = -1;
	bool = 0;
	if (ft_strchr(sh->cmds[sh->v], '='))
		bool = 1;
	while (sh->expenv[++i])
	{
		if (bool == 1 && sh->myenv[i])
			free(sh->myenv[i]);
		free(sh->expenv[i]);
	}
	return (bool);
}

void	export_var(t_data *sh)
{
	char	**tmp;
	int		bool;

	
	sh->j = -1;
	if (check_var_name(sh->cmds[sh->v]))
		get_error_message(sh->cmds[sh->v], 9);
	tmp = ft_calloc(sizeof(char *), array_size(sh->expenv) + 2);
	bool = 0;
	while (sh->expenv[++sh->j])
	{
		if (!ft_strcmp(check_var(sh->cmds[sh->v]), \
			check_var(sh->expenv[sh->j])))
		{
			tmp[sh->j] = malloc(sizeof(char) * (ft_strlen(sh->cmds[sh->v]) + 1));
			ft_strlcpy(tmp[sh->j], sh->cmds[sh->v], ft_strlen(sh->cmds[sh->v]) + 1);
			bool = 1;
			continue ;
		}
		tmp[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->expenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->j], sh->expenv[sh->j], \
			(ft_strlen(sh->expenv[sh->j]) + 1));
	}
	if (bool == 0)
	{
		tmp[sh->j] = malloc(sizeof(char) * (ft_strlen(sh->cmds[sh->v]) + 1));
		ft_strlcpy(tmp[sh->j], sh->cmds[sh->v], ft_strlen(sh->cmds[sh->v]) + 1);
	}
	tmp[++sh->j] = NULL;
	bool = check_free(sh);
	update_envs(sh, tmp, bool);
}
// SEPARER LA FONCTION ET FAIRE UNE FONCTION POUR COMPTER LE NOMBRE DE VARIABLE SANS '=' À ENLEVER AU MALLOC

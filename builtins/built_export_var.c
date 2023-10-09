/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:18:56 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/07 12:51:34 by ykifadji         ###   ########.fr       */
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

void	update_envs(t_data *sh, char **tmp)
{
	sh->j = -1;
	sh->expenv = malloc(sizeof(char *) * array_size(tmp));
	if (sh->bool == 1)
		sh->myenv = malloc(sizeof(char *) * \
			(array_size(tmp) - undeclared_var(tmp)));
	while (tmp[++sh->j])
	{
		if (sh->bool == 1 && ft_strchr(tmp[sh->j], '='))
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
	if (sh->bool == 1)
		sh->myenv[sh->j] = NULL;
	sh->expenv[sh->j] = NULL;
}

void	export_var(t_data *sh)
{
	char	**tmp;

	if (check_var_name(sh->cmds[sh->v]))
		get_error_message(sh->cmds[sh->v], 9);
	sh->j = -1;
	tmp = ft_calloc(sizeof(char *), array_size(sh->expenv) + 2);
	sh->bool = 0;
	while (sh->expenv[++sh->j])
	{
		if (!ft_strcmp(check_var(sh->cmds[sh->v]), \
			check_var(sh->expenv[sh->j])))
		{
			tmp[sh->j] = malloc(sizeof(char) * \
				(ft_strlen(sh->cmds[sh->v]) + 1));
			ft_strlcpy(tmp[sh->j], sh->cmds[sh->v], \
				ft_strlen(sh->cmds[sh->v]) + 1);
			sh->bool = 1;
			continue ;
		}
		tmp[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->expenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->j], sh->expenv[sh->j], \
			(ft_strlen(sh->expenv[sh->j]) + 1));
	}
	end_function(sh, tmp);
}

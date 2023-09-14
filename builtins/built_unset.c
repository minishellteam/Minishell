/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/13 11:44:08 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_env(t_data *sh, char **tmp)
{
	sh->j = -1;
	sh->myenv = malloc(sizeof(char *) * array_size(tmp));
	while (tmp[++sh->j])
	{
		sh->myenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		//free(tmp[sh->j]);
	}
	//free(tmp);
	sh->myenv[sh->j + 1] = NULL;
}
// PROBLEME SUR UNSET CA SUPPRIME TROP DE VAR

void	built_unset(t_data *sh)
{
	char	**tmp;
	char	**arg;

	sh->j = -1;
	tmp = malloc(sizeof(char *) * array_size(sh->myenv));
	arg = ft_split(sh->cmds[0], ' ');
	while (sh->myenv[++sh->j])
	{
		if (!ft_strncmp(arg[1], sh->myenv[sh->j], ft_strlen(arg[1])))
		{
			free(sh->myenv[sh->j]);
			sh->j++;
		}
		tmp[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->j], sh->myenv[sh->j], \
			(ft_strlen(sh->myenv[sh->j]) + 1));
		free(sh->myenv[sh->j]);
	}
	tmp[sh->j + 1] = NULL;
	free(sh->myenv);
	update_env(sh, tmp);
}

// void	export_var(char *var)
// {
// 	char	**tmp;

// 	sh->j = -1;
// 	tmp = malloc(sizeof(char *) * (array_size(sh->myenv) + 2));
// 	while (sh->myenv[++sh->j])
// 	{
// 		tmp[sh->j] = malloc(sizeof(char) \
// 			* (ft_strlen(sh->myenv[sh->j]) + 1));
// 		ft_strlcpy(tmp[sh->j], sh->myenv[sh->j], \
// 			(ft_strlen(sh->myenv[sh->j]) + 1));
// 		free(sh->myenv[sh->j]);
// 	}
// 	ft_strlcpy(tmp[sh->j + 1], var, ft_strlen(var));
// 	tmp[sh->j + 2] = NULL;
// 	update_env(tmp);
// }

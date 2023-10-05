/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/05 14:00:55 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_data *sh, char **tmp)
{
	sh->j = -1;
	sh->expenv = malloc(sizeof(char *) * array_size(tmp));
	while (tmp[++sh->j])
	{
		sh->expenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->expenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	//free(tmp);
	sh->expenv[sh->j] = NULL;
}

void	search_var(t_data *sh, char **tmp)
{
	sh->c = 0;
	while (sh->expenv[++sh->j])
	{
		if (!ft_strcmp(check_var(sh->cmds[sh->i]), check_var(sh->expenv[sh->j])))
		{
			free(sh->expenv[sh->j]);
			sh->j++;
		}
		tmp[sh->c] = malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->c], sh->expenv[sh->j], \
			(ft_strlen(sh->expenv[sh->j]) + 1));
		free(sh->expenv[sh->j]);
		sh->c++;
	}
	//free(sh->expenv);
	tmp[sh->c] = NULL;
	update_env(sh, tmp);
}

void	built_unset(t_data *sh)
{
	char	**tmp;

	sh->j = -1;
	sh->i = 0;
	while (sh->cmds[++sh->i])
	{
		if (sh->i == 1)
			tmp = malloc(sizeof(char *) * array_size(sh->expenv));
		sh->j = -1;
		search_var(sh, tmp);
	}
}

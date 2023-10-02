/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/22 15:11:36 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_data *sh, char **tmp)
{
	sh->j = -1;
	sh->myenv = malloc(sizeof(char *) * array_size(tmp));
	while (tmp[++sh->j])
	{
		sh->myenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	//free(tmp);
	sh->myenv[sh->j] = NULL;
}

void	search_var(t_data *sh, char **tmp)
{
	sh->c = 0;
	while (sh->myenv[++sh->j])
	{
		if (!ft_strcmp(check_var(sh->cmds[sh->i]), check_var(sh->myenv[sh->j])))
		{
			free(sh->myenv[sh->j]);
			sh->j++;
			printf("pass\n");
		}
		tmp[sh->c] = malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->c], sh->myenv[sh->j], \
			(ft_strlen(sh->myenv[sh->j]) + 1));
		free(sh->myenv[sh->j]);
		sh->c++;
	}
	free(sh->myenv);
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
			tmp = malloc(sizeof(char *) * array_size(sh->myenv));
		sh->j = -1;
		search_var(sh, tmp);
	}
}
// REFAIRE UNSET EN SE BASANT SUR L'ENV EXPORT
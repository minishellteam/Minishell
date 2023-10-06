/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/06 11:10:57 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_expenv(t_data *sh, char **tmp)
{
	sh->j = -1;
	while (tmp[++sh->j])
	{
		sh->expenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->expenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	sh->expenv[sh->j] = NULL;
}

static void	update_myenv(t_data *sh, char **tmp)
{
	sh->j = -1;
	while (tmp[++sh->j])
	{
		sh->myenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	sh->myenv[sh->j] = NULL;
}

void	search_var(t_data *sh, char **tmp)
{
	sh->c = 0;
	sh->j = -1;
	while (sh->expenv[++sh->j])
	{
		printf("j = %d\n", array_size(sh->expenv));
		if (!ft_strcmp(check_var(sh->cmds[sh->i]), check_var(sh->expenv[sh->j])))
		{
			free(sh->expenv[sh->j]);
			sh->j++;
		}
		tmp[sh->c] = malloc(sizeof(char) \
			* (ft_strlen(sh->expenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->c], sh->expenv[sh->j], \
			(ft_strlen(sh->expenv[sh->j]) + 1));
		printf("exp: %s\n", tmp[sh->c]);
		free(sh->expenv[sh->j]);
		sh->c++;
	}
	//free(sh->expenv);
	tmp[sh->c] = NULL;
	update_expenv(sh, tmp);
}

void	search_var_env(t_data *sh, char **tmp)
{
	sh->c = 0;
	sh->j = -1;
	while (sh->myenv[++sh->j])
	{
		if (!ft_strcmp(check_var(sh->cmds[sh->i]), check_var(sh->myenv[sh->j])))
		{
			free(sh->myenv[sh->j]);
			sh->j++;
		}
		tmp[sh->c] = malloc(sizeof(char) \
			* (ft_strlen(sh->myenv[sh->j]) + 1));
		ft_strlcpy(tmp[sh->c], sh->myenv[sh->j], \
			(ft_strlen(sh->myenv[sh->j]) + 1));
		free(sh->myenv[sh->j]);
		sh->c++;
	}
	//free(sh->myenv);
	tmp[sh->c] = NULL;
	update_myenv(sh, tmp);
}

void	built_unset(t_data *sh)
{
	char	**tmp;
	char	**tmp2;

	sh->i = 0;
	while (sh->cmds[++sh->i])
	{
		if (sh->i == 1)
			tmp = malloc(sizeof(char *) * array_size(sh->expenv));
		if (sh->i == 1)
			tmp2 = ft_calloc(sizeof(char *), array_size(sh->myenv) + 1);
		search_var(sh, tmp);
		printf("pass\n");
		search_var_env(sh, tmp2);
	}
}

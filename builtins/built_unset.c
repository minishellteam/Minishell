/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 08:58:33 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/09 15:43:22 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_expenv(t_data *sh, char **tmp)
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
	free(tmp);
	sh->expenv[sh->j] = NULL;
}

static void	update_myenv(t_data *sh, char **tmp)
{
	sh->j = -1;
	sh->myenv = malloc(sizeof(char *) * (array_size(tmp - undeclared_var(tmp))));
	while (tmp[++sh->j])
	{
		sh->myenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(tmp[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], tmp[sh->j], \
			(ft_strlen(tmp[sh->j]) + 1));
		free(tmp[sh->j]);
	}
	free(tmp);
	sh->myenv[sh->j] = NULL;
}

void	search_var_env(t_data *sh, char **tmp)
{
	sh->c = 0;
	sh->j = -1;
	while (sh->myenv[++sh->j])
	{
		get_tmp_myenv(sh, tmp);
	}
	free(sh->myenv);
	tmp[sh->c] = NULL;
	update_myenv(sh, tmp);
}

void	search_var(t_data *sh, char **tmp)
{
	sh->c = 0;
	sh->j = -1;
	while (sh->expenv[++sh->j])
	{
		get_tmp_expenv(sh, tmp);
	}
	free(sh->expenv);
	tmp[sh->c] = NULL;
	update_expenv(sh, tmp);
}

void	built_unset(t_data *sh)
{
	char	**tmp;
	char	**tmp2;

	sh->i = 0;
	while (sh->cmds[++sh->i])
	{
		if (sh->i == 1)
			tmp = ft_calloc(sizeof(char *), array_size(sh->expenv));
		if (sh->i == 1)
			tmp2 = ft_calloc(sizeof(char *), array_size(sh->myenv));
		search_var(sh, tmp);
		search_var_env(sh, tmp2);
	}
}

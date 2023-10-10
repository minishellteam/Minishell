/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:25:15 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/10 11:03:35 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	undeclared_var(char **tmp)
{
	int	res;
	int	i;

	res = 0;
	i = -1;
	while (tmp[++i])
		if (!ft_strchr(tmp[i], '='))
			res++;
	return (res);
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
		if (bool == 1 && sh->myenv && sh->myenv[i])
			free(sh->myenv[i]);
		free(sh->expenv[i]);
	}
	if (bool == 1)
		free(sh->myenv);
	free(sh->expenv);
	return (bool);
}

void	end_function(t_data *sh, char **tmp)
{
	if (sh->bool == 0)
	{
		tmp[sh->j] = malloc(sizeof(char) * (ft_strlen(sh->cmds[sh->v]) + 1));
		ft_strlcpy(tmp[sh->j], sh->cmds[sh->v], ft_strlen(sh->cmds[sh->v]) + 1);
	}
	tmp[++sh->j] = NULL;
	sh->bool = check_free(sh);
	update_envs(sh, tmp);
}

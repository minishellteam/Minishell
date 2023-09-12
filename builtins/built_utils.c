/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:39:01 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/12 11:02:45 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(t_data *sh)
{
	int	j;

	j = 0;
	while (sh->export->env[j] || sh->export->exp[j])
	{
		if (sh->export->env[j])
			free(sh->export->env[j]);
		if (sh->export->exp[j])
			free(sh->export->exp[j]);
		j++;
	}
	free(sh->export->env);
	free(sh->export->exp);
}

void	built_pwd(t_data *sh)
{
	char	buffer[BUFF_SIZE];

	if (!ft_strncmp(sh->cmds[0], "pwd", 3) && ft_strlen(sh->cmds[0]) == 3)
	{
		if (getcwd(buffer, BUFF_SIZE))
			printf("%s\n", buffer);
		else
			handle_error("minishell: ", 1);
	}
}

void	built_cd(t_data *sh)
{
	char	**tmp;

	if (!ft_strncmp(sh->cmds[0], "cd", 2))
	{
		tmp = ft_split(sh->line, ' ');
		if (chdir(tmp[1]) == -1)
			handle_error("minishell$ ", 1);
	}
}

void	built_env(t_data *sh)
{
	int	i;

	i = -1;
	if (!ft_strncmp(sh->cmds[0], "env", 3))
	{
		while (sh->myenv[++i])
			printf("%s\n", sh->myenv[i]);
	}
}

void	my_env(t_data *sh)
{
	sh->j = -1;
	sh->myenv = malloc(sizeof(char *) * len_env(sh->env));
	while (sh->env[++sh->j])
	{
		sh->myenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->env[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], sh->env[sh->j], \
			(ft_strlen(sh->env[sh->j]) + 1));
	}
	sh->myenv[sh->j + 1] = NULL;
}

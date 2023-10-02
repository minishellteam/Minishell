/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:39:01 by ykifadji          #+#    #+#             */
/*   Updated: 2023/10/02 11:02:58 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(t_data *sh)
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

void	built_pwd(void)
{
	char	buffer[BUFF_SIZE];

	if (getcwd(buffer, BUFF_SIZE))
		printf("%s\n", buffer);
	else
		perror("minishell");
}

void	built_cd(t_data *sh)
{
	if (chdir(sh->cmds[1]) == -1)
	{
		perror("minishell");
		set_exit_status(EXIT_FAILURE);
	}
}

void	built_env(t_data *sh)
{
	int	i;

	i = -1;
	while (sh->myenv[++i])
		printf("%s\n", sh->myenv[i]);
}

void	my_env(t_data *sh)
{
	sh->j = -1;
	sh->myenv = malloc(sizeof(char *) * array_size(sh->env));
	while (sh->env[++sh->j])
	{
		sh->myenv[sh->j] = malloc(sizeof(char) \
			* (ft_strlen(sh->env[sh->j]) + 1));
		ft_strlcpy(sh->myenv[sh->j], sh->env[sh->j], \
			(ft_strlen(sh->env[sh->j]) + 1));
	}
	sh->myenv[sh->j] = NULL;
}

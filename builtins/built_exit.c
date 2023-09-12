/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:09:27 by ykifadji          #+#    #+#             */
/*   Updated: 2023/09/12 10:53:52 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_exit(void)
{
	// if (sh->export->env || sh->export->exp)
	// 	free_tab();
	exit(EXIT_SUCCESS);
}

static void	arg_error(t_data *sh)
{
	char	*new;
	int		i;
	int		j;

	i = 4;
	while (sh->line[++i])
	{
		if (!ft_isdigit(sh->line[i]))
		{
			new = malloc(sizeof(char) * (ft_strlen(sh->line) - 3));
			i = 4;
			j = -1;
			while (sh->line[++i] && sh->line[i] != ' ')
				new[++j] = sh->line[i];
			new[j + 1] = '\0';
			printf("minishell: exit: %s: numeric argument required\n",
				new);
			free(new);
			new = NULL;
			return ;
		}
	}
}

void	built_exit(t_data *sh)
{
	int	i;

	i = 4;
	sh->line = ft_strtrim(sh->line, " ");
	if (!ft_strncmp(sh->line, "exit", 4) && !ft_strchr(sh->line, '|'))
	{
		if (ft_strlen(sh->line) > 4 && sh->line[4] != ' ')
			return ;
		printf("exit\n");
		if (ft_strlen(sh->line) > 4)
			arg_error(sh);
		if (ft_strlen(sh->line) > 4 && sh->line[5] == '1')
			exit(EXIT_FAILURE);
		else if (ft_strlen(sh->line) > 4 && sh->line[5] == '0')
			exit(EXIT_SUCCESS);
		free_exit();
	}
}

void	ft_builts(t_data *sh)
{
	sh->cmds = ft_split(sh->line, '|');
	built_exit(sh);
	//built_echo();
	built_pwd(sh);
	built_cd(sh);
	built_export(sh);
	built_env(sh);
	built_unset(sh);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/05 22:47:17 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int x)
{
	if (x == 1)
		perror(message);
	else if (x == 0)
		ft_putstr_fd(message, 2);
	free(message);
}

void	get_error_message(char *error, int x)
{
	char	*begin_msg;
	char	*end_msg;
	char	*error_msg;

	begin_msg = "minishell: ";
	error_msg = NULL;
	if (x == 0)
	{
		end_msg = ": undefined token\n";
		error_msg = ft_strjoin(begin_msg, error);
		error_msg = ft_strjoingnl(error_msg, end_msg, 0);
	}
	else if (x == 1)
	{
		end_msg = "syntax error near unexpected token `";
		error_msg = ft_strjoin (begin_msg, end_msg);
		error_msg = ft_strjoingnl(error_msg, error, 0);
		error_msg = ft_strjoingnl(error_msg, "\'\n", 0);
	}
	else if (x == 2)
	{
		end_msg = "syntax error: expecting closing quote\n";
		error_msg = ft_strjoin(begin_msg, end_msg);
	}
	else if (x == 3)
	{
		end_msg = ": No such file of directory\n";
		error_msg = ft_strjoin(begin_msg, error);
		error_msg = ft_strjoingnl(error_msg, end_msg, 0);
	}
	handle_error(error_msg, 0);
}

void	print_tab(char **tab)
{
	int	y;

	y = -1;
	while (tab[++y])
		printf("%s\n", tab[y]);
	printf("\n");
}

void	free_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}

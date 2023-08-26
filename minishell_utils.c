/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/22 12:21:09 by mkerkeni         ###   ########.fr       */
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
	handle_error(error_msg, 0);
}

void	print_str_of_str(char **str, int row)
{
	int	y;

	y = -1;
	while (++y < row)
		printf("%s", str[y]);
	printf("\n");
}

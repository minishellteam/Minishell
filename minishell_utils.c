/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/23 10:34:28 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int x)
{
	if (x == 1)
		perror(message);
	else if (x == 0)
		ft_putstr_fd(message, 2);
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
		end_msg = ": command not found\n";
		error_msg = ft_strjoin(begin_msg, error, 0);
		error_msg = ft_strjoin(error_msg, end_msg, 0);
	}
	else if (x == 1)
	{
		end_msg = "syntax error near unexpected token `";
		error_msg = ft_strjoin (begin_msg, end_msg, 0);
		error_msg = ft_strjoin(error_msg, error, 0);
		error_msg = ft_strjoin(error_msg, "\'\n", 0);
	}
	else if (x == 2)
	{
		end_msg = "syntax error: expecting closing quote\n";
		error_msg = ft_strjoin(begin_msg, end_msg, 0);
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

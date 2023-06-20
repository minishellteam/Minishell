/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:18:54 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/16 09:21:37 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(char *message, int x)
{
	if (x == 1)
		perror(message);
	else if (x == 0)
		ft_putstr_fd(message, 2);
	//exit(EXIT_FAILURE);
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
		error_msg = ft_strjoin(begin_msg, error);
		error_msg = ft_strjoin(error_msg, end_msg);
	}
	else if (x == 1)
	{
		end_msg = "syntax error near unexpected token `";
		error_msg = ft_strjoin (begin_msg, end_msg);
		error_msg = ft_strjoin(error_msg, error);
		error_msg = ft_strjoin(error_msg, "'\n");
	}
	//handle_error(error_msg, 0);
}

void	print_str_of_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		ft_printf("%s", str[i]);
		ft_printf(" ");
	}
	ft_printf("\n");
}

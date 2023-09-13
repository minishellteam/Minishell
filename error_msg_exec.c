/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:17:16 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/13 22:22:53 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_error(char *error, char *begin, char *err_msg, char *end)
{
	end = ": Command not found\n";
	err_msg = ft_strjoin(begin, error);
	err_msg = ft_strjoingnl(err_msg, end, 0);
	return (err_msg);
}

char	*get_exit_error(char *error, char *begin, char *err_msg, char *end)
{
	char	*exit_msg;

	exit_msg = "exit: ";
	end = ": numeric argument required\n";
	err_msg = ft_strjoin(begin, exit_msg);
	err_msg = ft_strjoingnl(err_msg, error, 0);
	err_msg = ft_strjoingnl(err_msg, end, 0);
	return (err_msg);
}

char	*get_mult_arg_err(char *error, char *begin, char *err_msg, char *end)
{
	end = "too many arguments\n";
	err_msg = ft_strjoin(begin, error);
	err_msg = ft_strjoingnl(err_msg, end, 0);
	return (err_msg);
}

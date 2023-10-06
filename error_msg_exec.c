/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:17:16 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/06 11:06:23 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_error(char *error, char *begin, char *err_msg)
{
	char	*end;

	end = NULL;
	set_exit_status(127);
	end = ": Command not found\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

char	*get_exit_error(char *error, char *begin, char *err_msg)
{
	char	*exit_msg;
	char	*end;

	end = NULL;
	set_exit_status(255);
	exit_msg = "exit: ";
	end = ": numeric argument required\n";
	err_msg = ft_strjoin(begin, exit_msg, 0);
	err_msg = ft_strjoin(err_msg, error, 1);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

char	*get_mult_arg_err(char *error, char *begin, char *err_msg)
{
	char	*end;

	end = NULL;
	set_exit_status(1);
	end = "too many arguments\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

char	*get_file_error(char *error, char *begin, char *err_msg)
{
	char	*end;

	end = NULL;
	set_exit_status(1);
	end = ": No such file of directory\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

char	*get_dir_error(char *error, char *begin, char *err_msg)
{
	char	*end;

	end = NULL;
	set_exit_status(126);
	end = ": Is a directory\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

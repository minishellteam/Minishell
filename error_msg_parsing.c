/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:43:46 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/14 12:21:18 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_bad_tok_err(char *error, char *begin, char *err_msg, char *end)
{
	g_exit_code = 1;
	end = ": undefined token\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

static char	*get_syntax_err(char *error, char *begin, char *err_msg, char *end)
{
	g_exit_code = 2;
	end = "syntax error near unexpected token `";
	err_msg = ft_strjoin(begin, end, 0);
	err_msg = ft_strjoin(err_msg, error, 1);
	err_msg = ft_strjoin(err_msg, "\'\n", 1);
	return (err_msg);
}

static char	*get_quote_error(char *begin, char *err_msg, char *end)
{
	g_exit_code = 1;
	end = "syntax error: expecting closing quote\n";
	err_msg = ft_strjoin(begin, end, 0);
	return (err_msg);
}

static char	*get_file_error(char *error, char *begin, char *err_msg, char *end)
{
	end = ": No such file of directory\n";
	err_msg = ft_strjoin(begin, error, 0);
	err_msg = ft_strjoin(err_msg, end, 1);
	return (err_msg);
}

void	get_error_message(char *error, int x)
{
	char	*begin_msg;
	char	*end_msg;
	char	*error_msg;

	begin_msg = "minishell: ";
	end_msg = NULL;
	error_msg = NULL;
	if (x == 0)
		error_msg = get_bad_tok_err(error, begin_msg, error_msg, end_msg);
	else if (x == 1)
		error_msg = get_syntax_err(error, begin_msg, error_msg, end_msg);
	else if (x == 2)
		error_msg = get_quote_error(begin_msg, error_msg, end_msg);
	else if (x == 3)
		error_msg = get_file_error(error, begin_msg, error_msg, end_msg);
	else if (x == 4)
		error_msg = get_cmd_error(error, begin_msg, error_msg, end_msg);
	else if (x == 5)
		error_msg = get_exit_error(error, begin_msg, error_msg, end_msg);
	else if (x == 6)
		error_msg = get_mult_arg_err("exit: ", begin_msg, error_msg, end_msg);
	handle_error(error_msg, 0);
}

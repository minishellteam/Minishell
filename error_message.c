/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:43:46 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/07 13:29:36 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_bad_tok_err(char *error, char *begin, char *err_msg, char *end)
{
	end = ": undefined token\n";
	err_msg = ft_strjoin(begin, error);
	err_msg = ft_strjoingnl(err_msg, end, 0);
	return (err_msg);
}

static char	*get_syntax_err(char *error, char *begin, char *err_msg, char *end)
{
	end = "syntax error near unexpected token `";
	err_msg = ft_strjoin (begin, end);
	err_msg = ft_strjoingnl(err_msg, error, 0);
	err_msg = ft_strjoingnl(err_msg, "\'\n", 0);
	return (err_msg);
}

static char	*get_quote_error(char *begin, char *err_msg, char *end)
{
	end = "syntax error: expecting closing quote\n";
	err_msg = ft_strjoin(begin, end);
	return (err_msg);
}

static char	*get_file_error(char *error, char *begin, char *err_msg, char *end)
{
	end = ": No such file of directory\n";
	err_msg = ft_strjoin(begin, error);
	err_msg = ft_strjoingnl(err_msg, end, 0);
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
	handle_error(error_msg, 0);
}

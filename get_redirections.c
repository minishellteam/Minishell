/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 19:17:20 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/07 09:35:44 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_file_fd(char *file_name, int x)
{
	int	fd;

	if (x == 0)
		fd = open(file_name, O_RDONLY, 0777);
	else if (x == 1)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
		get_error_message(file_name, 3);
	return (fd);
}

static int	check_infile(t_tok *tmp, int fd)
{
	if (!ft_strncmp(tmp->prev->type, "LESSER", ft_strlen(tmp->type)))
	{
		if (fd && fd != -1 && fd != -2)
			close(fd);
		fd = get_file_fd(tmp->tok, 0);
	}
	return (fd);
}

int	get_in_redir(t_vars *var)
{
	t_tok	*tmp;
	int		fd;

	tmp = var->pipeline;
	fd = 0;
	while (tmp && ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
	{
		if (fd == -1)
			return (-1);
		if (!ft_strncmp(tmp->type, "FILE", ft_strlen(tmp->type)))
			fd = check_infile(tmp, fd);
		else if (!ft_strncmp(tmp->type, "LIMITER", ft_strlen(tmp->type)))
		{
			if (fd && fd != -1 && fd != -2)
				close(fd);
			fd = -2;
		}
		tmp = tmp->next;
	}
	return (fd);
}

static int	check_outfile(t_tok *tmp, int fd)
{
	if (!ft_strncmp(tmp->prev->type, "GREATER", ft_strlen(tmp->type)))
	{
		if (fd != 1 && fd != -1)
			close(fd);
		fd = get_file_fd(tmp->tok, 1);
	}
	else if (!ft_strncmp(tmp->prev->type, "D_GREATER", ft_strlen(tmp->type)))
	{
		if (fd != 1 && fd != -1)
			close(fd);
		fd = get_file_fd(tmp->tok, 2);
	}
	return (fd);
}

int	get_out_redir(t_vars *var)
{
	t_tok	*tmp;
	int		fd;

	tmp = var->pipeline;
	fd = 1;
	while (tmp && ft_strncmp(tmp->type, "PIPE", ft_strlen(tmp->type)))
	{
		if (fd == -1)
			return (-1);
		if (!ft_strncmp(tmp->type, "FILE", ft_strlen(tmp->type)))
			fd = check_outfile(tmp, fd);
		tmp = tmp->next;
	}
	return (fd);
}

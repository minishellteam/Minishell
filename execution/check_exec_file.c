/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:05:40 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/27 00:07:07 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_permission(char *file)
{
	char	*message;

	message = ft_strjoin("minishell: ", file, 0);
	file += 2;
	if (access(file, X_OK))
	{
		perror(message);
		free(message);
		if (errno == EACCES)
			set_exit_status(126);
		else
			set_exit_status(127);
		return (1);
	}
	free(message);
	return (0);
}

int	check_if_dir(char *cmd)
{
	struct stat	f_infos;

	if (stat(cmd, &f_infos) != -1)
	{
		if (S_ISDIR(f_infos.st_mode))
		{
			get_error_message(cmd, 8);
			return (1);
		}
	}
	return (0);
}

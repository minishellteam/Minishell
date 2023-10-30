/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_empty_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:30 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/10/29 15:09:28 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_null_stdout(void)
{
	int		null_fd;

	null_fd = open("/dev/null", O_WRONLY);
	dup2(null_fd, STDOUT_FILENO);
	close(null_fd);
}

void	read_stdin(void)
{
	int		tmp_fd[2];
	char	*input;
	char	*new_input;

	pipe(tmp_fd);
	input = get_next_line(0);
	if (!input)
		return ;
	new_input = ft_substr(input, 0, ft_strlen(input) - 1);
	free(input);
	write(tmp_fd[1], new_input, ft_strlen(new_input));
	free(new_input);
	close(tmp_fd[1]);
	dup2(tmp_fd[0], STDIN_FILENO);
	close(tmp_fd[0]);
}

int	is_empty_pipe(int fd)
{
	char	buf[1];
	int		ret;

	ret = read(fd, buf, sizeof(buf));
	if (ret == 0)
		return (1);
	return (0);
}

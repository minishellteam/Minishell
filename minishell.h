/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/08 08:41:43 by ykifadji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/inc/libft.h"
# include "libft/inc/get_next_line.h"
# include "libft/inc/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
#include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data {
	int		ac;
	char	**av;
	char	**env;
	char	**cmds;
	char	*path;
	char	*var;
	char	*cmd_line;
}			t_data;

int		main(int ac, char **av, char **env);

void	parsing(t_data *cmd, char *line);

char	**get_env_vars(t_data cmd);

void	handle_error(char *message, int x);
void	print_str_of_str(char **str);

void	signal_handler(int signal, siginfo_t *sa, void *content);

#endif

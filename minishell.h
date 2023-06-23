/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykifadji <ykifadji@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/23 08:42:34 by ykifadji         ###   ########.fr       */
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

# define BUFF_SIZE 10000

typedef struct s_export {
	char	**env;
	char	**exp;
	int		j;
}	t_export;

typedef struct s_data {
	t_export	*export;
	int		ac;
	char	**av;
	char	**env;
	char	**cmds;
	char	*path;
	char	*var;
	char	*line;
	char	*var_line;
	char	*final;
	int		i;
	int		j;
	int		c;
	int		n;
	char	**echo;
}			t_data;

int		main(int ac, char **av, char **env);

void	parsing(t_data *cmd, char *line);

char	**get_value_vars(t_data cmd);

void	handle_error(char *message, int x);
void	get_error_message(char *error, int x);
void	print_str_of_str(char **str);

void	signal_handler(int signal, siginfo_t *sa, void *content);

/*===================BUILTINS=========================*/
void	ft_builts(t_data *cmd);
void	built_exit(t_data *cmd);
void	built_echo(t_data *cmd);
void	built_export(t_data *cmd);
void	built_pwd(t_data *cmd);
void	built_cd(t_data *cmd);
void	built_env(t_data *cmd);
void	free_tab(t_data *cmd);

#endif

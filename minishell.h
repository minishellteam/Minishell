/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/11 11:13:15 by mkerkeni         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

# ifndef HISTORY_SIZE
#  define HISTORY_SIZE 100
# endif

typedef struct s_data {
	int		ac;
	char	**av;
	char	**env;
	char	**cmds;
	char	*path;
	char	*var;
	char	*line;
	char	*var_line;
	char	**history;
	int		hist_fd;
	int		rows;
	int		line_pos;
}			t_data;

int		main(int ac, char **av, char **env);

void	parsing(t_data *cmd, char *line);

char	*get_value_vars(t_data cmd);

void	handle_error(char *message, int x);
void	print_str_of_str(char **str, int row);

void	add_line_to_history(t_data *cmd);
void	init_history(char **history);
void	get_old_history(t_data *cmd);
void	clear_history_file(t_data *cmd);

#endif

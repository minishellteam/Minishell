/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/07 12:43:03 by mkerkeni         ###   ########.fr       */
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

typedef struct s_command {
	int		ac;
	char	**av;
	char	**env;
	char	*path;
	char	*var;
	char	*cmd_line;
}			t_command;

int		main(int ac, char **av, char **env);

char	*get_value_vars(t_command cmd);

void	handle_error(char *message);
void	print_str_of_str(char **str);

#endif

/*static char	*handle_var(char *new_line, char *cmd_line, int i)
{
	char	*var;
	char	*value;
	int		j;

	i++;
	j = i;
	while (ft_isalnum(cmd_line[i]) || cmd_line[i] == '_')
		i++;
	var = get_var(cmd_line, j, i);
	value = getenv(var);
	if (!value)
		new_line = replace_var_by_nothing(new_line, ft_strlen(var));
	else
		new_line = replace_var_by_value(new_line, value, ft_strlen(var));
	free(var);
	var = NULL;
	value = NULL;
	return (new_line);
}*/
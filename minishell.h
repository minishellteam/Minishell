/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/06/16 10:43:02 by mkerkeni         ###   ########.fr       */
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

typedef struct s_tok {
	char			*token;
	struct s_tok	*next;
}					t_tok;

typedef struct s_data {
	int		ac;
	char	**av;
	char	**env;
	char	**cmds;
	char	*path;
	char	*var;
	char	*line;
	char	*var_line;
	char	*history[HISTORY_SIZE];
	int		hist_fd;
	int		rows;
	t_tok	*tokens;
	int		x;
}			t_data;

t_data	g_sh;

enum e_toktype {
	STRING,
	PIPE,
	GREATER,
	LESSER,
	DOUBLE_GREATER,
	DOUBLE_LESSER,
} ;

int		main(int ac, char **av, char **env);

//void	parsing(t_data *cmd, char *line);

char	*get_value_vars(t_data cmd);
char	*replace_var_by_value(char *line, char *value, int start, int end);
char	*handle_var(char *new_line, char *var, char *value);

void	handle_error(char *message, int x);
void	print_str_of_str(char **str, int row);
void	get_error_message(char *error, int x);

int		is_special_char(char token);
int		ft_isspace(char token);
char	*check_chevrons(int token_len);

char	*get_quoted_token(char *token_start, char *token_end, int token_len);
char	*get_s_quote_tok(char *token_start, char *token_end, int token_len);

void	add_line_to_history(void);
void	init_history(char **history);
void	get_old_history(void);
void	clear_history_file(void);

void	tokenize_line(void);
char	*get_double_chevron_token(int token_len);

t_tok	*ft_lst_new(char *token);
void	ft_lst_add_back(t_tok **lst, t_tok *new);
void	print_list(t_tok *token);
t_tok	*ft_lst_last(t_tok *lst);
int		ft_lst_size(t_tok *lst);

#endif

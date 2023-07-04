/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/07/04 10:46:28 by mkerkeni         ###   ########.fr       */
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
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef HISTORY_SIZE
#  define HISTORY_SIZE 100
# endif

typedef struct s_tok {
	char			*tok;
	char			*type;
	struct s_tok	*next;
	struct s_tok	*prev;
}					t_tok;

# define BUFF_SIZE 10000

typedef struct s_export {
	char	**env;
	char	**exp;
}	t_export;

typedef struct s_data {
	t_export	*export;
	int			ac;
	char		**av;
	char		**env;
	char		**cmds;
	char		*path;
	char		*var;
	char		*line;
	char		*var_line;
	char		*history[HISTORY_SIZE];
	int			hist_fd;
	int			rows;
	t_tok		*toks;
	int			empty;
	t_tok		*rest;
	int			x;
	char		*final;
	int			i;
	int			j;
	int			c;
	int			n;
	char		**echo;
}				t_data;

t_data	g_sh;

enum e_toktype {
	STRING,
	EMPTY,
	PIPE,
	GREATER,
	LESSER,
	DOUBLE_GREATER,
	DOUBLE_LESSER,
} ;

int		main(int ac, char **av, char **env);

void	add_line_to_history(void);
void	init_history(char **history);
void	get_old_history(void);
void	clear_history_file(void);

void	tokenize_line(void);

t_tok	*get_token_type(t_tok *toks);

void	parse_tokens(void);

int		check_before_pipe(t_tok *pipeline);
int		get_nb_of_pipes(void);
int		check_double_pipe(void);

void	remove_empty_tok(void);
void	get_options(void);
void	get_files(void);
void	get_commands(void);
void	get_arguments(void);

char	*get_value_vars(char *str);
char	*replace_var_by_value(char *line, char *value, int start, int end);
char	*handle_var(char *new_line, char *var, char *value);
char	*search_and_replace_var(char *token, char *var, char *value);
char	get_quote_type(char *token);

void	handle_error(char *message, int x);
void	print_str_of_str(char **str, int row);
void	get_error_message(char *error, int x);

int		is_special_char(char token);
int		ft_isspace(char token);
int		is_forbidden_char(char token);
int		check_question_mark(char *token);

//char	*get_non_quoted_tok(char *token, char *token_start, char *token_end, int token_len);
//char	*get_quoted_token(char *start, char *end, int token_len, char q_type);
int		check_quote_in_str(char *token_start, char *token_end);

char	*get_double_chevrons_token(int token_len);
int		check_chevrons(t_tok *pipeline);
int		is_chevron(char	*token, int x);

t_tok	*ft_lst_new(char *token);
void	ft_lst_add_back(t_tok **lst, t_tok *new);
void	print_list(t_tok *token, int x);
t_tok	*ft_lst_last(t_tok *lst);
int		ft_lst_size(t_tok *lst);
void	free_list(t_tok *lst);

void	parse_tokens(void);

int		handle_quotes(void);

void	signal_handler(int signal, siginfo_t *sa, void *content);

/*===================BUILTINS=========================*/
void	ft_builts(t_data *cmd);
void	built_exit(t_data *cmd);
void	built_echo(t_data *cmd);
//void	built_export(t_data *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/07/05 16:01:24 by mkerkeni         ###   ########.fr       */
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
	char		**env;
	char		**cmds;
	char		*var;
	char		*line;
	char		*history[HISTORY_SIZE];
	int			hist_fd;
	int			rows;
	t_tok		*toks;
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

int		main(int ac, char **av, char **env);

void	handle_error(char *message, int x);
void	print_str_of_str(char **str, int row);
void	get_error_message(char *error, int x);

void	signal_handler(int signal, siginfo_t *sa, void *content);

/*===================HISTORY=========================*/

void	add_line_to_history(void);
void	init_history(char **history);
void	get_old_history(void);
void	clear_history_file(void);

/*===================LEXER============================*/

void	tokenize_line(void);

int		is_special_char(char token);
int		ft_isspace(char token);
int		is_forbidden_char(char token);
int		check_question_mark(char *token);
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

t_tok	*get_token_type(t_tok *toks);

/*===================PARSER===========================*/

void	parse_tokens(void);

int		check_before_pipe(t_tok *pipeline);
int		get_nb_of_pipes(void);
int		check_double_pipe(void);

void	remove_empty_tok(void);
void	get_files(void);

/*===================EXPANDER=========================*/

int		handle_quotes(void);
int		expand_vars(void);
char	*get_vars(t_tok *token);

char	get_quote_type(char *token);
char	*replace_var_by_value(char *line, char *value, int start, int end);
char	*search_and_replace_var(char *token, char *var, char *value);

/*===================BUILTINS=========================*/

void	ft_builts(t_data *cmd);
void	built_exit(t_data *cmd);
void	built_echo(t_data *cmd);
//void	built_export(t_data *cmd);

#endif

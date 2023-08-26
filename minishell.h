/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/08/27 00:06:25 by mkerkeni         ###   ########.fr       */
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

typedef struct s_hist {
	char		*history[HISTORY_SIZE];
	int			rows;
	int			hist_fd;
}				t_hist;

typedef struct s_input {
	char			*input;
	struct s_input	*next;
}					t_input;

typedef struct s_tok {
	char			*tok;
	char			*type;
	struct s_tok	*next;
	struct s_tok	*prev;
}					t_tok;

typedef struct s_vars {
	t_tok	*toks;
	t_tok	*tok;
	t_tok	*pipeline;
	t_tok	*pipeline_end;
	char	*token;
	char	*start;
	char	*end;
	char	*var;
	char	*value;
	int		len;
	char	*line;
	int		x;
	t_input	*data;
}			t_vars;

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
	char		*final;
	int			i;
	int			j;
	int			c;
	int			n;
	char		**echo;
}				t_data;

int		main(int ac, char **av, char **env);

void	handle_error(char *message, int x);
void	print_str_of_str(char **str, int row);
void	get_error_message(char *error, int x);

void	signal_handler(int signal, siginfo_t *sa, void *content);

/*==================================HISTORY===================================*/

void	add_line_to_history(char *line, char **history, int hist_fd);
void	init_history(char **history);
void	get_old_history(t_hist *hist);
void	clear_history_file(t_hist *hist);

/*===================================LEXER====================================*/

int		tokenize_line(char *line, t_vars *var);

int		is_special_char(char token);
int		ft_isspace(char token);
int		is_forbidden_char(char token);
int		check_question_mark(char *line, char *token);
int		check_quote_in_str(t_vars *var, char *start, char *end);

char	*get_double_chevrons_token(t_vars *var);
int		check_chevrons(t_vars *var);
int		is_chevron(char	*token, int x);

char	*get_ex_code_token(t_vars *var);
t_tok	*get_token_type(t_tok *toks);

t_tok	*ft_lst_new(char *token);
void	ft_lst_add_back(t_tok **lst, t_tok *new);
void	print_list(t_tok *token, int x);
t_tok	*ft_lst_last(t_tok *lst);
int		ft_lst_size(t_tok *lst);
void	free_list(t_tok **lst, int x);

t_input	*ft_lstnew_input(void *content);
t_input	*ft_lstlast_input(t_input *lst);
void	ft_lstadd_back_input(t_input **lst, t_input *new);
void	print_list_input(t_input *input);
void	free_list_input(t_input *lst, int x);

int		check_limiter(t_vars *var);

/*==================================EXPANDER==================================*/

int		handle_quotes(t_vars *var);
int		expand_vars(void);

char	*get_var(char *token, char *var, char *value, int x);
char	get_quote_type(char *token);

/*===================================PARSER===================================*/

int		parse_tokens(t_vars *var);

int		check_before_pipe(t_vars *var);
int		get_nb_of_pipes(t_tok *toks);
int		check_double_pipe(t_tok *toks);

//void	remove_empty_tok(void);
void	get_files(t_tok *toks);

/*===================================BUILTINS=================================*/

void	ft_builts(t_data *cmd);
void	built_exit(t_data *cmd);
void	built_echo(t_data *cmd);
//void	built_export(t_data *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerkeni <mkerkeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 09:54:19 by mkerkeni          #+#    #+#             */
/*   Updated: 2023/09/29 15:23:05 by mkerkeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/inc/libft.h"
# include "Libft/inc/get_next_line.h"
# include "Libft/inc/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

# define BUFF_SIZE 1000

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

typedef struct s_cmd {
	char	**args;
	int		pid;
	int		fdin;
	int		fdout;
}			t_cmd;

typedef struct s_vars {
	char	**my_env;
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
	int		bool;
	int		pipe_nb;
	t_input	**data;
	t_cmd	*cmd;
	int		orig_stdin;
	int		orig_stdout;
	int		tmp_fd;
	int		here_doc[2];
}			t_vars;

typedef struct s_export {
	char	**env;
	char	**exp;
	int		j;
}	t_export;

typedef struct s_data {
	t_export	*export;
	char		**env;
	char		**myenv;
	char		**expenv;
	char		**cmds;
	char		*var;
	char		*final;
	char		*line;
	int			i;
	int			j;
	int			c;
	int			n;
	int			v;
	char		**echo;
}				t_data;

int		main(int ac, char **av, char **env);

void	get_error_message(char *error, int x);

char	*get_cmd_error(char *error, char *begin, char *err_msg, char *end);
char	*get_exit_error(char *error, char *begin, char *err_msg, char *end);
char	*get_mult_arg_err(char *error, char *begin, char *err_msg, char *end);
char	*get_file_error(char *error, char *begin, char *err_msg, char *end);

void	handle_error(char *message, int x);
void	print_tab(char **tab);
void	free_tab(char	**tab);
void	init_data(t_vars *var);
void	*ft_malloc(size_t size);
int		*get_exit_status(void);
void	set_exit_status(int status);

void	signal_handler(int signal, siginfo_t *sa, void *content);

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
void	free_list_input(t_input **lst, int nb, int x);

void	get_limiter(t_tok *toks);
int		check_limiter(t_vars *var);

/*===================================PARSER===================================*/

int		parse_tokens(t_vars *var);

int		check_before_pipe(t_vars *var);
int		get_nb_of_pipes(t_tok *toks);
int		check_double_pipe(t_tok *toks);

//void	remove_empty_tok(void);
void	get_files(t_tok *toks);

/*==================================EXPANDER==================================*/

int		handle_quotes(t_vars *var);
int		expand_vars(void);

char	*get_var(char *token, t_vars *var, int x);
void 	get_value(t_vars *var);
char	get_quote_type(char *token);

/*==============================REDIRECTIONS==================================*/

int		get_cmd_infos(t_vars *var);
int		get_in_redir(t_vars *var);
int		get_out_redir(t_vars *var);
void	free_structures(t_cmd *cmd, int stop);

/*=============================EXECUTION======================================*/

int		create_processes(t_vars *var, t_data *sh);
void	get_here_doc_input(t_vars *var, int *pfd, int i);
void	create_multiple_processes(t_vars *var);
void	get_std_stream(int fd, int std_stream);

int		wait_for_processes(t_vars *var);
int		exec_cmd(t_vars *var, int i);

int		is_builtin(char *cmd);
void	handle_builtin(t_vars *var, t_data *sh);
void	exec_builtin(t_data *sh);

/*===================================BUILTINS=================================*/

void	my_env(t_data *sh);
void	exp_env(t_data *sh);
int		array_size(char **array);
void	free_array(t_data *sh);
void	update_env(t_data *sh, char **tmp);

void	built_pwd(void);
void	built_exit(t_data *sh);
void	built_echo(t_data *sh);
void	built_cd(t_data *sh);
void	built_env(t_data *sh);
void	built_unset(t_data *sh);
void	built_export(t_data *sh);
void	export_var(t_data *sh);

#endif

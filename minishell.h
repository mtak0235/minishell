#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>
#include "libft/libft.h"
# include <signal.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>

# define MAX_LINE 30
# define DOUBLE 1
# define SINGLE 2
# define PIPE 3
# define BACK_SLASH 4

int		g_exit_code;

typedef struct	s_utils
{
	int			flags;
	int			strlen;
	char		*string;
	char		*result;
	char		**env;
	int			i;
	int			j;
}				t_utils;

typedef struct s_pipe
{
	int		status;
	int		*fd;
	int		i;
	pid_t	pid;
}				t_pipe;

typedef struct	s_parse
{
	t_utils		utils;
	t_pipe		pipe;
	char		*args[MAX_LINE];
}				t_parse;

void	init_shell(void);
void	print_dir(void);
void	init_minishell(char *tokens, char **env);

int		get_next_line(char **line);
void 	redirect_in(t_parse *p, char *fileName);
void 	redirect_out(char *fileName);
char	**absolute_path();

int		ft_strchcmp(char *str, char c);
char	*ft_strndup(char *src, int size);
char	*ft_strtok(char *s, char *d);

void	check_quotes(char line, int *flags);
void	initialize_structs(t_parse *p, t_utils *u, char **env);

char 	*tokenize(char *input);
char	**ft_strtok_dimensional_array(char **s, char *c);

void	check_path_n_execve(char **cmds, char **env);
void 	run(char *args[], char **env);
void 	execute_pipe(t_parse *p);
void	run_or_pipe(t_parse *p);
void	dup_n_run_pipe(t_parse *p, char **args);

void	close_n_free_pipe(t_parse *p, char **tmp);
void	print_error_message(char *cmd, char *message);

int		syntax_error_check(char *args);
void	error_message(char **cmds);


typedef struct s_history
{
	struct s_history	*next;
	struct s_history	*prev;
	void				*content;
	int					idx;
}				t_history;

t_list *g_envlst;

void init_list(char **env);
int is_builtin(char *cmd, char *av);
void only_export();
void func_export(char *str);
int is_exportformat(char *str);
int is_whitespace(char c);
void free_machine(char **strs);
void del_next_node(t_list *target);
char *get_env(char *str, t_list *envlst);
t_list	*search_env_address_return_prev(char *str, t_list *envlst);
int func_cd(char *dir);
void func_unset(char *str);
void func_env();

/* not builtin func manipulating by mtak */

typedef struct		s_path
{
	char			*path;
	struct s_path	*next;
}					t_path;

typedef struct		s_term
{
	struct termios	term;
	struct termios	save;
	char			*cm;
	char			*ce;
}					t_term;

typedef struct		s_cmd
{
	char			**av;
	int				ac;
	int				type;
	int				pip[2];
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	int				has_equal;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct		s_keypos
{
	int				col;
	int				row;
}					t_keypos;

typedef struct		s_save
{
	char			*input;
	int				flag;
	struct s_save	*prev;
	struct s_save	*next;
}					t_save;

typedef struct	s_set
{
	t_history	*last_node;
	int			up_cnt;
	int			down_cnt;
}				t_set;

typedef struct		s_state
{
	t_token			*token_head;
	t_env			*env_head;
	t_cmd			*cmd_head;
	t_path			*path_head;
	t_term			t;
	t_save			*save_head;
	int				s_flag;
	char			*input;
	char			*input2;
	int				is_fork;
	int				ret;
	t_keypos		cur;
	t_keypos		max;
	t_keypos		start;
	t_set			set;
}					t_state;

t_state g_state;

void	init_state(t_state *state);
void	handle_signal(int signo);
void	prepare_token_and_cmd(t_state *state);
void	init_state(t_state *state);
void	get_str(t_state *s);
void	reset_save(t_state *s);
void	delete_save(t_save *save);
void	init_term(t_state *s);
int		term_loop(t_state *s);
void	set_cursor_w(t_state *s);
void	set_cursor(int *col, int *row);
int		get_nbr_len(int n);
void	init_set_cursor(char buf[255], int *read_ret, int *i, int *flag);
void	handle_keycode(t_state *s, int keycode);
int	ft_isprint(int c);
void	print_save_char(t_state *s, char c);
void	handle_eof(t_state *s, char *input);
void	put_backspace(t_state *s);
int		ft_putchar(int c);
void	move_cursor(t_state *s);
void	press_up(t_state *s);
char	*delete_last_char(char *str);
t_save	*push_front_save(char *input, t_save *old_head, int flag);
void	clear_prompt(t_state *s);
void	press_down(t_state *s);

t_history	*ft_lstnew_history(void *content);
t_history	*ft_lstlast_history(t_history *lst);
void	ft_lstadd_back_history(t_history **lst, t_history *new);
void	save_history(t_state *s);
int					ft_strncmp_env(char *s1, char *s2, unsigned int n);

#endif

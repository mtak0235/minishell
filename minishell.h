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

/* mtak lib */
#include "dirent.h"

# define MAX_LINE 1024
# define DOUBLE 1
# define SINGLE 2
# define PIPE 3

void	init_shell(void);
void	print_dir(void);
void	init_minishell(char *tokens, char **env);

int		get_next_line(char **line);
void 	redirect_in(char *fileName);
void 	redirect_out(char *fileName);
char	**absolute_path();

int		ft_strchcmp(char *str, char c);
char		*ft_strndup(char *src, int size);
char	*ft_strtok(char *s, char *d);

void	check_quotes(char line, int *flags);

char 	*tokenize(char *input);
char	**ft_strtok_dimensional_array(char **s, char *c);



void	check_path_n_execve(char **cmds, char **env);
void 	run(char *args[], char **env);
void 	execute_pipe(char **args, int flags, char **env);
void	run_or_pipe(char **args, int *i, int *flags, char **env);



void	dup_n_run_pipe(int i, int *fd, int pipe_num, char **args, char **env);

/* not builtin func manipulating by mtak */
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

#endif

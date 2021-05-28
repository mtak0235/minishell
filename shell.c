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
#include "./libft/libft.h"

#include "mtak.h"

#define MAX_LINE 1024 // The maximum length command
# define DOUBLE 1
# define SINGLE 2

int should_run = 1;  // flag to determine when to exit program
int should_wait = 1; // flag to determine if process should run in the background

int		get_next_line(char **line)
{
	char buf[1] = {0};
	char *save = malloc(1000);
	int rd = 0, count = 0;

	if(!line) return (-1);
	save[0] = 0;
	while ((rd = read(0, buf, 1)) > 0)
	{
		if (buf[0] == '\n') break;
		save[count++] = buf[0];
		save[count] = 0;
	}
	*line = save;
	return (rd);
}

void redirectIn(char *fileName)
{
    int in = open(fileName, O_RDONLY);
    dup2(in, 0);
    close(in);
}

/**
 * Redirects stdout to a file.
 * 
 * @param fileName the file to redirect to
 */
void redirectOut(char *fileName)
{
    int out = open(fileName, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

/**
 * Runs a command.
 * 
 * *args[] the args to run
 */

char	**absolute_path()
{
	char **path;
	char *tmp;
	int	i;

	tmp = getenv("PATH");
	path = ft_split(tmp, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
		i++;		
	}
	return (path);
}

int		ft_strchcmp(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_path_n_execve(char **cmds, char **env)
{
	char **path;
	char	*tmp;
	int	i;

	if (ft_strchcmp(cmds[0], '/'))
		execve(cmds[0], cmds, env);
	else
	{
		path = absolute_path();
		i = 0;
		while (path[i])
		{
			tmp = ft_strjoin(path[i], cmds[0]);
			free(path[i]);
			execve(tmp, cmds, env);
			free(tmp);
			i++;
		}
	}
}

void run(char *args[], char **env)
{
    pid_t pid;
    if (strcmp(args[0], "exit") != 0)
        {
            pid = fork();
            if (pid < 0) { 
                fprintf(stderr, "Fork Failed");
            }
            else if ( pid == 0) { /* child process */
                check_path_n_execve(args, env);
            }
            else { /* parent process */
                if (should_wait) {
                    waitpid(pid, NULL, 0);
                } else {
                    should_wait = 0;
                }
            }
            redirectIn("/dev/tty");
            redirectOut("/dev/tty");
        }
    else {
        should_run = 0;
    }
}

/**
 * Creates a pipe.
 * 
 * @param args [description]
 */
void createPipe(char *args[], char **env)
{
    int fd[2];
    pipe(fd);

    dup2(fd[1], 1);
    close(fd[1]);

    printf("args = %s\n", *args);

    run(args, env);

    dup2(fd[0], 0);
    close(fd[0]);
}

void	check_quotes(char line, int *flags)
{
	if (!*flags && line == '"')
		*flags |= DOUBLE;
	else if (!*flags && line == '\'')
		*flags |= SINGLE;
	else if (*flags == DOUBLE && line == '"')
		*flags &= ~ DOUBLE;
	else if (*flags == SINGLE && line == '\'')
		*flags &= ~ SINGLE;
}

char *tokenize(char *input)
{
    int i;
    int j = 0;
	int	flags;
    char *tokenized = (char *)malloc((MAX_LINE * 2) * sizeof(char));

    // add spaces around special characters
	flags = 0;
    for (i = 0; i < strlen(input); i++) {
		check_quotes(input[i], &flags);
        if (flags || input[i] != '>' && input[i] != '<' && input[i] != '|' && input[i] != ';') {
            tokenized[j++] = input[i];
        } else {
            tokenized[j++] = ' ';
            tokenized[j++] = input[i];
            tokenized[j++] = ' ';
        }
    }
    tokenized[j++] = '\0';
    return tokenized;
}

/**
 * Runs a basic shell.
 * 
 * @return 0 upon completion
 */

void	init_shell(void)
{
	printf("\n\n");
	printf("-----------------------------------------\n");
	printf("----- Napark & Seokim's Micro Shell -----\n");
	printf("------------- Enjoy It! -----------------\n");
	printf("-----------------------------------------\n\n");
}

void	print_dir(void)
{
	char	cwd[256];
	getcwd(cwd, sizeof(cwd));
	write(1, cwd, strlen(cwd));
	write(1, "> ", 2);
}

char		*ft_strndup(char *src, int size)
{
	char	*arr;
	int		i;

	i = 0;
	if (size < 0)
		size = 1;
	if (!(arr = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i <= size)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}


char 	**minishell_split(char *line, char c)
{
	int	i;
	int	j;
	int	flags;
	int count;
	char **tmp;

	i = 0;
	flags = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == c)
			count++;
		i++;
	}
	if (!(tmp = (char **)malloc(sizeof(char*) * (count + 2))))
		return (NULL);
	i = 0;
	count = 0;
	j = 0;
	while (line[i])
	{
		check_quotes(line[i], &flags);
		if (!flags && line[i] == c)
		{
			tmp[count] = ft_strndup(line + j, i - j - 1);
			count++;
			j = i + 1;
		}
		i++;
	}
	tmp[count++] = ft_strdup(line + j);
	tmp[count] = 0;
	return (tmp);
}

char	*ft_strtok(char *s, char *d)
{
	static char *input;
	char	*res;
	char	*tmp;
	int		flags;
	int		i;

	if (s != NULL)
		input = s;
	if (input == (void *)0)
		return (NULL);
	i = 0;
	flags = 0;
	while (input[i])
	{
		check_quotes(input[i], &flags);
		if (!flags && input[i] == d[0])
		{
			while (input[i] == d[0])
				i++;
			tmp = ft_strdup(input + i);
			input[i - 1] = '\0';
			res = input;
			input = tmp;
			return (res);
		}
		i++;
	}
	res = input;
	input = NULL;
	return (res);
}

int main(int ac, char **av, char **env)
{
    char *args[MAX_LINE]; // command line arguments
    char	*input;
	int		flags;
	char *tmp;

    init_shell();
    while (should_run) {
		print_dir();
		get_next_line(&input);
printf("input : %s\n", input);

        char *tokens;
        tokens = tokenize(input);

        if (tokens[strlen(tokens) - 1] == '&') {
            should_wait = 0;
            tokens[strlen(tokens) - 1] = '\0';
        }
		char *arg = ft_strtok(tokens, " ");
        int i = 0;

/* export 구현 */
		t_list *envlst;
		init_list(&envlst, env);
		if (!ft_strncmp(input, "export", 6))
			func_export(input, &envlst);
/* unset 구현 */
		if (!ft_strncmp(input, "unset", 5))
			func_unset(input, &envlst);
/* env 구현 */
		if (!ft_strncmp(input, "env", 3))
			func_env(envlst);


        while (arg) {
            if (*arg == '<') {
                redirectIn(ft_strtok(NULL, " "));
            } else if (*arg == '>') {
                redirectOut(ft_strtok(NULL, " "));
            } else if (*arg == '|') {
                args[i] = NULL;
                createPipe(args, env);
                i = 0;
            } 
            else if (*arg == ';') {
                args[i] = NULL;
                run(args, env);
                i = 0;
            }
            else {
                args[i] = arg;
                i++;
            }
			arg = ft_strtok(NULL, " ");
			printf("arg : %s\n", arg);
        }
        args[i] = NULL;
  
        run(args, env);
    }
    return 0;
}
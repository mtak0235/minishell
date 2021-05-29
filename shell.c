#include "minishell.h"


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

void redirect_in(char *file_name)
{
    int in = open(file_name, O_RDONLY);
    dup2(in, 0);
    close(in);
}

void redirect_out(char *file_name)
{
    int out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

void	redirect_append(char *file_name)
{
	int	out = open(file_name, O_WRONLY | O_APPEND | O_CREAT, 0600);
	dup2(out, 1);
	close(out);
}

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

	if (!is_builtin(cmds[0], cmds[1]))
		return ;
	else
	{
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
                //if (should_wait) {
                    waitpid(pid, NULL, 0);
                //} else {
                //    should_wait = 0;
                //}
            }
            redirect_in("/dev/tty");
            redirect_out("/dev/tty");
        }
    else {
        should_run = 0;
    }
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
	int	len;
    char *tokenized = (char *)malloc((MAX_LINE * 2) * sizeof(char));

	flags = 0;
	len = ft_strlen(input);
	i = 0;
    while (i < len)
	{
		check_quotes(input[i], &flags);
        if (flags || input[i] != '>' && input[i] != '<' && input[i] != '|' && input[i] != ';')
            tokenized[j++] = input[i];
        else
		{
            tokenized[j++] = ' ';
			if (input[i + 1] && input[i] == '>' && input[i + 1] == '>')
            	tokenized[j++] = input[i++];
			tokenized[j++] = input[i];
            tokenized[j++] = ' ';
        }
		i++;
    }
    tokenized[j++] = '\0';
    return tokenized;
}

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
	write(1, "> ", 3);
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
			input[i++] = '\0';
			while (input[i] == d[0])
				i++;
			tmp = ft_strdup(input + i);
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

void	dup_n_run_pipe(int i, int *fd, int pipe_num, char **args, char **env)
{
	int	j;

	if (i > 0)
		dup2(fd[(i - 1) * 2], 0);
	j = 0;
	while (j < (pipe_num * 2))
		close(fd[j++]);
	check_path_n_execve(args, env);
}

char	**ft_strtok_dimensional_array(char **s, char *c)
{
	static char **args;
	char **res;
	int	i;

	i = 0;
	if (s != NULL)
		args = s;
	if (args == (void *)0)
		return (NULL);
	res =  args;
	while (args[i])
	{
		if (args[i][0] == *c)
		{
			free(args[i]);
			args[i] = NULL;
			args = args + i + 1;
			return (res);
		}
		i++;
	}
	res = args;
	args = NULL;
	return (res);
}

void execute_pipe(char **args, int flags, char **env)
{
	int	status;
	int	i;
	int *fd;
	char **tmp;
	pid_t pid;

	i = 0;
	tmp = ft_strtok_dimensional_array(args, "|");
	if (!(fd = malloc(sizeof(int) * (flags * 2))))
		return ;
	while (i < flags)
		pipe(fd + (i++ * 2));
	i = 0;
	while (i < flags)
	{
		if ((pid = fork()) == 0)
		{
			dup2(fd[i * 2 + 1], 1);
			dup_n_run_pipe(i, fd, flags, tmp, env);
		}
		tmp = ft_strtok_dimensional_array(NULL, "|");
		i++;
	}
	if ((pid = fork()) == 0)
		dup_n_run_pipe(i, fd, flags, tmp, env);
	i = 0;
	while (i < flags * 2)
		close(fd[i++]);
	i = -1;
	while (++i <= flags)
		wait(&status);
	redirect_in("/dev/tty");
    redirect_out("/dev/tty");
	free(fd);
}

void	run_or_pipe(char **args, int *i, int *flags, char **env)
{
	args[*i] = NULL;
	if (!*flags)
		run(args, env);
	else
		execute_pipe(args, *flags, env);
	*flags = 0;
	*i = 0;
}

void	redirection(char *arg, char *file_name)
{
	if (*arg == '<')
		redirect_in(file_name);
	else if (*arg == '>')
	{
		if (arg[1] == '>')
			redirect_append(file_name);
		else
			redirect_out(file_name);
	}
}

void	init_minishell(char *tokens, char **env)
{
	char *args[MAX_LINE];
	int	flags;
	char *arg;
	int	i;

	arg = ft_strtok(tokens, " ");
	i = 0;
	flags = 0;
	while (arg) 
	{
		if (*arg == '<' || *arg == '>')
		{
			redirection(arg, ft_strtok(NULL, " "));
			if ((arg = ft_strtok(NULL, " ")) != NULL)
			{
				run_or_pipe(args, &i, &flags, env);
				continue ;
			}
		}
		else if (*arg == '|')
		{
			flags++;
			args[i++] = arg;
		}
		else if (*arg == ';')
			run_or_pipe(args, &i, &flags, env);
		else
			args[i++] = arg;
		arg = ft_strtok(NULL, " ");
	}
	run_or_pipe(args, &i, &flags, env);
}

int main(int ac, char **av, char **env)
{
    char	*args[MAX_LINE];
    char	*input;
	char	*tokens;

    init_shell();
	/* mtak */
	init_list(env);

    while (should_run) {
		print_dir();
		get_next_line(&input);
        tokens = tokenize(input);
		init_minishell(tokens, env);
    }
    return 0;
}
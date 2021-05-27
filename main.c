#include "minishell.h"

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

char		*ft_strndup(char *src, size_t size)
{
	char	*arr;
	int		i;

	i = 0;
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

char	return_seperator(char *line)
{
	int	i;
	int flags;

	i = 0;
	flags = 0;
	while (line[i])
	{
		check_quotes(line[i], &flags);
		if (flags == 0 && line[i] == ';')
			return (';');
		else if (flags == 0 && line[i] == '|')
			return ('|');
		i++;
	}
	return ('E');
}

char	**absolute_path()
{
	char	*tmp;
	char	**path;
	int		i;
	
	i = 0;
	tmp = getenv("PATH");
	path = ft_split(tmp, ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = tmp;
		i++;
	}
	return (path);
}

void	redirection_in(char *file_name)
{
	int in;

	in = open(file_name, O_RDONLY);
	dup2(in, 0);
	close(in);
}

void	redirection_out(char *file_name)
{
	int	out;

	out = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600);
	dup2(out, 1);
	close(out);
}

void	run2(t_main *glob, char *args)
{
	pid_t pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		//에러처리하기
		printf("Error");
	}
	else if (pid == 0)
	{
		//상대경로일때 절대경로일때 확인해서 넘겨야?
		run(glob, args);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
	}
	//redirection_in("/dev/tty");
	//redirection_out("/dev/tty");
}

//void	create_pipe(t_main *glob, char *args)
//{
//	int	fd[2];
//	pipe(fd);

//	dup2(fd[1], STDIN_FILENO);
//	close(fd[1]);

//	run2(glob, args);

//	dup2(fd[0], 0);
//	close(fd[0]);
//}

void	run(t_main *glob, char *res)
{
	//flag = PIPE가 넘어왔다 치고
	//pid_t	*pid;
	char **cmds;
	char	**path;
	char	*tmp;
	int	i;
	int	flags = PIPE;

	i = 0;
	cmds = minishell_split(res, ' ');
	while (cmds[i])
	{
		cmds[i] = save_without_special_chr(cmds[i]);
		i++;
	}
	//그냥 절대path로 들어올때와 아닐 때 구분하기
	path = absolute_path();
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], cmds[0]);
		free(path[i]);
		execve(tmp, cmds, glob->env);
		free(tmp);
		i++;
	}
}

//void	check_needs_dimensional_array(char *line)
//{
//	char ch;
//	char **tmp;
//	int	i;

//	i = 0;
//	ch = return_seperator(line);
//	if (ch == 'E')
//		//run(line);
//		printf("hello");
//	else
//	{
//		tmp = minishell_split(line, ch);
//		while (tmp[i])
//		{
//			create_dimensional_array(tmp[i], ch);
//			i++;
//		}
//	}
//}

void	create_sub_dimensional_array(char *cmd, char ch)
{
	char **tmp;
	int i;

	tmp = minishell_split(cmd, ch);
	i = 0;
	while (tmp[i])
	{
		printf("tmp[%d]: %s\n", i, tmp[i]);
		i++;
	}
}

void	create_dimensional_array(t_main *glob, char *cmds, char ch)
{
	char **tmp;
	char	chr;
	int		i;

	i = 0;
	tmp = minishell_split(cmds, ch);
	while (tmp[i])
	{
		chr = return_seperator(tmp[i]);
		if (chr == 'E')
			run2(glob, tmp[i]);
		//else
		//{
		//	create_sub_dimensional_array(tmp[i], chr);
		//}
		i++;
	}
}

char	*save_without_special_chr(char *cmd)
{
	int i;
	int j;
	int flags;
	char *new_cmd;

	i = 0;
	j = 0;
	flags = 0;
	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			flags |= BACK_SLASH;
		//check_quotes로 묶어주기
		else if (flags != BACK_SLASH && cmd[i] == '"')
			flags |= DOUBLE;
		else if (flags != BACK_SLASH && cmd[i] == '\'')
			flags |= SINGLE;
		else
		{
			new_cmd[j] = cmd[i];
			j++;
			if (flags == BACK_SLASH)
				flags &= ~ BACK_SLASH;
		}
		i++;
	}
	new_cmd[j] = 0;
	free(cmd);
	return (new_cmd);
}

t_list	*create_node(char *line)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	////error처리해주기
	new->content = line;
	new->next = NULL;
	return (new);
}

void	minishell(t_main *glob)
{
	char	ch;

	ch = return_seperator(glob->line);
	if (ch == 'E')
		run2(glob, glob->line);
	else
		create_dimensional_array(glob, glob->line, ch);
}

void	initialize(t_main *glob, char **env)
{
	glob->env = env;
	glob->line = NULL;
}

void	save_input_history(t_main *glob)
{
	t_list	*new;

	if (glob->line)
		new = create_node(glob->line);
	ft_lstadd_back(&glob->history, new);
}

int		main(int ac, char *av[], char *env[])
{
	t_main	glob;

	init_shell();
	initialize(&glob, env);
	while (1)
	{
		print_dir();
		get_next_line(&glob.line);
		save_input_history(&glob);
		minishell(&glob);
	}
}

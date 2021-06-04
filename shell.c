#include "minishell.h"

int		get_next_line(char **line)
{
	char buf[1];
	char *save;
	int rd;
	int	count;

	save = malloc(100);
	rd = 0;
	count = 0;
	if(!line)
		return (-1);
	save[0] = 0;
	while ((rd = read(0, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			break ;
		save[count++] = buf[0];
		save[count] = 0;
	}
	*line = save;
	return (rd);
}

void	print_error_message(char *cmd, char *message)
{
	ft_putstr_fd("microShell: ", 2);
	if (cmd)
		ft_putstr_fd(cmd,2);
	ft_putstr_fd(message, 2);
	write(2, ":", 1);
	ft_putstr_fd(" No such file or directory\n", 2);
}

void redirect_in(t_parse *p, char *file_name)
{
    int in = open(file_name, O_RDONLY, 00700);
	if (in < 0)
	{
		print_error_message(0, file_name);
		p->pipe.status = 1;
		return ;
	}
    dup2(in, 0);
    close(in);
	// 나중에 고쳐야 함
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

	//여기 꼭 바꿔야함!!!!!!!!!!!!!!!
	tmp = ft_strdup(getenv("PATH"));
	if (tmp == NULL)
		return (NULL);
	path = ft_split(tmp, ':');
	free(tmp);
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

void	free_arrays(char **dim, int head)
{
	int	i;

	i = 0;
	while (dim[i])
		free(dim[i++]);
	if (head)
		free(dim);
}

char	*get_env_strjoin_n_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*return_errno(char **cmds)
{
	char *res;

	res = ft_itoa(g_exit_code);
	free_arrays(cmds, 1);
	return (res);
}

char	*link_env_arrays(char *res, char *rest, char **cmds, int j)
{
	if (res == NULL && rest)
	{
		res = rest;
		rest = NULL;
	}
	if (rest && res)
		res = get_env_strjoin_n_free(res, rest);
	if (j > 1 && res)
		res = get_env_strjoin_n_free(cmds[0], res);
	return (res);
}

char	*parse_env_var(char *str)
{
	t_utils u;
	char *env_name;

	initialize_structs(0, &u, NULL);
	u.env = ft_split(str, '$');
	if (u.env[0][0] == '?')
		return (return_errno(u.env));
	while (u.env[u.j])
		u.j++;
	while (u.env[u.j - 1][u.i] && ft_isalnum(u.env[u.j - 1][u.i]))
		u.i++;
	env_name = ft_strndup(u.env[u.j - 1], u.i - 1);
	if (u.env[u.j - 1][u.i] != '\0')
		u.string = ft_strdup(u.env[u.j - 1] + u.i);
		// #ㅇㅕ기 꼭 다시 바꿔야 함!!!!!!!!!!1
	u.result = ft_strdup(getenv(env_name));
	free(env_name);
	//이 부분이랑 double quote랑 관련된 부분 합칠 수 있을 듯 (다른 로직임)
	u.result = link_env_arrays(u.result, u.string, u.env, u.j);
	free_arrays(u.env, 1);
	return (u.result);
}

char	*clean_up_double_quote(char *cmds)
{
	t_utils u;

	initialize_structs(0, &u, NULL);
	if (!cmds)
		return (NULL);
	u.env = ft_split(cmds, '"');
	while (u.env[u.i])
	{
		if (ft_strchcmp(u.env[u.i], '$'))
		{
			u.string = parse_env_var(u.env[u.i]);
			free(u.env[u.i]);
			u.env[u.i] = u.string;
			if (u.string == NULL)
				u.j = 1;
		}
		if (u.j == 1)
			u.env[u.i] = u.env[u.i + 1];
		u.i++;
	}
	u.j = 0;
	u.result = ft_strdup(u.env[u.j++]);
	while (u.i > 1 && u.env[u.j])
		u.result = get_env_strjoin_n_free(u.result, u.env[u.j++]);
	free_arrays(u.env, 1);
	return (u.result);
}

char *clean_up_single_quote(char *cmds)
{
	char **tmp;
	char *res;
	int	i;

	i = 0;
	if (!ft_strncmp(cmds, "''", 2))
		return (NULL);
	tmp = ft_split(cmds, '\'');
	while (tmp[i])
		i++;
	if (i > 1)
		res = ft_strjoin(tmp[0], tmp[1]);
	else
		res = ft_strdup(*tmp);
	free_arrays(tmp, 1);
	return (res);
}

char	*clean_up_back_slash(char *str)
{
	char	**tmp;
	char	*ret;
	char	*res;
	int		len;

	len = 0;
	if (!str)
		return (NULL);
	tmp = ft_split(str, '\\');
	while (tmp[len])
		len++;
	ret = clean_up_double_quote(tmp[0]);
	if (len > 1)
		ret = get_env_strjoin_n_free(ret, tmp[1]);
	res = ret;
	len = 0;
	free_arrays(tmp, 1);
	return (res);
}

char	*is_only_n(char *str)
{
	int	i;
	int	count;
	char *res;

	i = 1;
	count = 0;
	while (str[i])
	{
		if (str[i++] != 'n')
			return (NULL);
		count++;
	}
	res = ft_strdup("-n");
	return (res);
}

void	check_echo_cmds(char **cmds)
{
	int i;
	char *tmp;

	i = 1;
	while (cmds[i])
	{
		if (cmds[i][0] == '-')
		{
			if ((tmp = is_only_n(cmds[i])) != NULL)
			{
				free(cmds[i]);
				cmds[i] = tmp;
			}
		}
		i++;
	}
}

void	clean_up_cmds(char **cmds)
{
	char	*tmp;
	int		i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i][0] == '"')
			tmp = clean_up_double_quote(cmds[i]);
		else if (cmds[i][0] == '\'')
			tmp = clean_up_single_quote(cmds[i]);
		else
			tmp = clean_up_back_slash(cmds[i]);
		//if (ft_strncmp(cmds[i], "", ft_strlen(cmds[i])))
		free(cmds[i]);
		cmds[i] = tmp;
		i++;
	}
	check_echo_cmds(cmds);
}

void	only_absolute_path(char **path, char **cmds, char **env)
{
	char *res;

	if (path == NULL && !ft_strncmp(cmds[0], "echo", 4))
	{
		res = ft_strjoin("/bin/", cmds[0]);
		free(cmds[0]);
		cmds[0] = res;
	}
	if (ft_strchcmp(cmds[0], '/'))
		execve(cmds[0], cmds, env);
	else if (path == NULL)
	{
		print_error_message(0, cmds[0]);
		exit(127);
	}
}

void	check_path_n_execve(char **cmds, char **env)
{
	char 	**path;
	char	*tmp;
	int		i;

	path = absolute_path();
	//is_builtin함수에서 path free해주는 것을 한번 해줘야 함
	if (!syntax_error_check(cmds[0]))
	{
		error_message(cmds);
		exit(127);
	}
	if (path && !is_builtin(cmds[0], cmds[1]))
	{
		free_arrays(path, 1);
		return ;
	}
	else
	{
		if (path == NULL || ft_strchcmp(cmds[0], '/'))
			only_absolute_path(path, cmds, env);
		else
		{
			i = 0;
			while (path[i])
			{
				tmp = ft_strjoin(path[i], cmds[0]);
				execve(tmp, cmds, env);
				free(tmp);
				i++;
			}
		}
	}
	free_arrays(path, 1);
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

void	initialize_structs(t_parse *p, t_utils *u, char **env)
{
	if (p)
	{
		p->utils.flags = 0;
		p->utils.strlen = 0;
		p->utils.string = NULL;
		p->utils.i = 0;
		p->utils.j = 0;
		p->utils.env = env;
	}
	if (u)
	{
		u->flags = 0;
		u->strlen = 0;
		u->result = NULL;
		u->string = NULL;
		u->i = 0;
		u->j = 0;
	}
}

char	*ft_substr_check(char *s1, char *s2, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == s2[j])
		{
			if (!ft_strncmp(s1 + i, s2, len))
				return (s2);
		}
		i++;
	}
	return (NULL);
}

void	syntax_error_message(char *input)
{
	ft_putstr_fd("microShell: ", 2);
	ft_putstr_fd("syntax error near unexpected token", 2);
	write(2, " `", 2);
	if (!ft_strncmp(input, ">>>", ft_strlen(input)) ||
	ft_substr_check(input, ">>>>", 4))
		ft_putstr_fd(input + 2, 2);
	else
		ft_putstr_fd(input, 2);
	write(2, "'", 1);
	write(2, "\n", 1);
	g_exit_code = 258;
}

int		return_syntax_error(char *input)
{
	char	*res;
	if (!*input)
		return (1);
	if (!ft_strncmp(input, ";", ft_strlen(input)) ||
	!ft_strncmp(input, "|", ft_strlen(input)) ||
	!ft_strncmp(input, ">>>", ft_strlen(input)))
	{
		syntax_error_message(input);
		return (1);
	}
	else if ((res = ft_substr_check(input, ";;", 2)) ||
	(res = ft_substr_check(input, "||", 2)) ||
	(res = ft_substr_check(input, ">>>>", 4)))
	{
		syntax_error_message(res);
		return (1);
	}
	return (0);
}

char *tokenize(char *input)
{
	t_utils	utils;
    
	initialize_structs(0, &utils, NULL);
	utils.string = (char *)malloc((MAX_LINE * 2) * sizeof(char));
	utils.strlen = ft_strlen(input);
    while (utils.i < utils.strlen)
	{
		check_quotes(input[utils.i], &utils.flags);
        if (utils.flags || input[utils.i] != '>' && input[utils.i] != '<' \
			&& input[utils.i] != '|' && input[utils.i] != ';')
            utils.string[utils.j++] = input[utils.i];
        else
		{
            utils.string[utils.j++] = ' ';
			if (input[utils.i] == '>' && input[utils.i + 1] == '>')
            	utils.string[utils.j++] = input[utils.i++];
			utils.string[utils.j++] = input[utils.i];
            utils.string[utils.j++] = ' ';
        }
		utils.i++;
    }
    utils.string[utils.j++] = '\0';
	free(input);
    return (utils.string);
}

void	init_shell(void)
{
	printf("\n\n");
	printf("-----------------------------------------\n");
	printf("------ Mtak & Seokim's Micro Shell ------\n");
	printf("------------- Enjoy It! -----------------\n");
	printf("-----------------------------------------\n\n");
}

void	print_dir(void)
{
	char	cwd[256];
	getcwd(cwd, sizeof(cwd));
	write(1, cwd, strlen(cwd));
	write(1, "$ ", 3);
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
	t_utils	u;
	static char *input;

	initialize_structs(0, &u, NULL);
	if (s != NULL)
		input = s;
	if (input == (void *)0)
		return (NULL);
	while (input[u.i])
	{
		check_quotes(input[u.i], &u.flags);
		if (!u.flags && input[u.i] == d[0])
		{
			input[u.i++] = '\0';
			while (input[u.i] == d[0])
				u.i++;
			u.string = ft_strdup(input + u.i);
			u.result = input;
			input = u.string;
			return (u.result);
		}
		u.i++;
	}
	u.result = input;
	input = NULL;
	return (u.result);
}

void	dup_n_run_pipe(t_parse *p, char **args)
{
	int	j;

	if (p->pipe.i > 0)
		dup2(p->pipe.fd[(p->pipe.i - 1) * 2], 0);
	j = 0;
	while (j < (p->utils.flags * 2))
		close(p->pipe.fd[j++]);
	check_path_n_execve(args, p->utils.env);
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

void	close_n_free_pipe(t_parse *p, char **tmp)
{
	p->pipe.i = 0;
	while (p->pipe.i < p->utils.flags * 2)
		close(p->pipe.fd[p->pipe.i++]);
	p->pipe.i = -1;
	while (++p->pipe.i <= p->utils.flags)
		wait(&p->pipe.status);
	//명령어 free하기 전에 status비교해서 값 넣어주기
	free_arrays(tmp, 0);
	free(p->pipe.fd);
}

void	execute_pipe(t_parse *p)
{
	char **tmp;

	p->pipe.i = 0;
	tmp = ft_strtok_dimensional_array(p->args, "|");
	if (!(p->pipe.fd = malloc(sizeof(int) * (p->utils.flags * 2))))
		return ;
	while (p->pipe.i < p->utils.flags)
		pipe(p->pipe.fd + (p->pipe.i++ * 2));
	p->pipe.i = 0;
	while (p->pipe.i < p->utils.flags)
	{
		if ((p->pipe.pid = fork()) == 0)
		{
			dup2(p->pipe.fd[p->pipe.i * 2 + 1], 1);
			dup_n_run_pipe(p, tmp);
		}
		free_arrays(tmp, 0);
		tmp = ft_strtok_dimensional_array(NULL, "|");
		p->pipe.i++;
	}
	if (*p->args && (p->pipe.pid = fork()) == 0)
		dup_n_run_pipe(p, tmp);
	close_n_free_pipe(p, tmp);
	// => 표준입력을 원래대로 되돌릴려고 이렇게 하신 것 같은데
	// => 이게 맞으면 redirect in 같이 쓰시면 안되고 함수를 따로 빼서 쓰셔야되고 
	//redirect_in(0, "/dev/tty");
    //redirect_out("/dev/tty");
}

int		syntax_error_check(char *args)
{
	const char *cmds = "cd echo ls grep rm cat pwd unset export env ENV wc";
	char **each_cmds;
	int	i;

	i = 0;
	each_cmds = ft_split(cmds, ' ');
	while (each_cmds[i])
	{
		if (ft_substr_check(args, each_cmds[i], ft_strlen(args)) != NULL)
		{
			while (each_cmds[i])
				free(each_cmds[i++]);
			free(each_cmds);
			return (1);
		}
		free(each_cmds[i]);
		i++;
	}
	free(each_cmds);
	return (0);
}

void	error_message(char **cmds)
{
	ft_putstr_fd("microShell: ", 2);
	ft_putstr_fd(cmds[0], 2);
	write(2, ":", 1);
	ft_putstr_fd(" command not found\n", 2);
	free_arrays(cmds, 0);
	// p->pipe.status = 127;
	//아래 부분 중복되지 않도록 하는 방법 구상해보기
	// p->utils.flags = 0;
	// p->utils.i = 0;
}

void	run_or_pipe(t_parse *p)
{
	//이 부분 이중 free되고 있지 않은지 잘 살펴보기
	//이 부분이 현재 문제가 되고 있는데, 이게 > string이 남아서 free해줬던 걸로
	//기억하는데 확인해보기
	/*이걸 왜 해줬지?? ; 여기서 릭이 나서 해준듯*/
	//if (p->utils.string != NULL)
	//	free(p->utils.string);
	p->args[p->utils.i] = NULL;
	//NULL 가드한건데 문제있는지 살피기
	if (!*p->args)
		return ;
	if (!ft_strncmp(p->args[0], "exit", 4))
		exit(EXIT_SUCCESS);
	clean_up_cmds(p->args);
	//내가 syntax_error_check을 파이프 안에 넣은 이유는 파이프 사이에 에러가 있을때 처리하려고 한거임
	// if (*p->args && !syntax_error_check(p->args[0]))
	// 	return (error_message(p));
	execute_pipe(p);
	p->utils.flags = 0;
	p->utils.i = 0;
}

void	redirection(t_parse *p, char *file_name)
{
	if (*p->utils.string == '<')
		redirect_in(p, file_name);
	else if (*p->utils.string == '>')
	{
		if (p->utils.string[1] == '>')
			redirect_append(file_name);
		else
			redirect_out(file_name);
	}
	free(p->utils.string);
	free(file_name);
	if ((p->utils.string = ft_strtok(NULL, " ")) != NULL &&
	*p->utils.string != '>' && *p->utils.string != '<')
	{
		if (*p->utils.string == '|')
		{
			free(p->utils.string);
			p->utils.string = ft_strtok(NULL, " ");
		}
		run_or_pipe(p);
	}
}

int		manipulate_error_code(int status)
{
	if (status == 256)
		status /= 256;
	else if (status == 11)
		status = 1;
	else if (status == 32512)
		status = 127;
	return (status);
}

void	init_minishell(char *tokens, char **env)
{
	t_parse p;

	initialize_structs(&p, 0, env);
	p.utils.string = ft_strtok(tokens, " ");
	while (p.utils.string) 
	{
		if (*p.utils.string == '<' || *p.utils.string == '>')
		{
			redirection(&p, ft_strtok(NULL, " "));
			continue ;
		}
		else if (*p.utils.string == '|')
		{
			p.utils.flags++;
			p.args[p.utils.i++] = p.utils.string;
		}
		else if (*p.utils.string == ';')
		{
			free(p.utils.string);
			run_or_pipe(&p);
		}
		else
			p.args[p.utils.i++] = p.utils.string;
		p.utils.string = ft_strtok(NULL, " ");
	}
	run_or_pipe(&p);
	g_exit_code = manipulate_error_code(p.pipe.status);
}




















void	clear_prompt(t_state *s)
{
	move_cursor(s);
	if (s->input)
		free(s->input);
	s->input = 0;
	s->s_flag = 0;
}

void	press_down(t_state *s)
{
	if (s->save_head == 0 || (s->save_head->prev == 0
			&& s->save_head->flag == 0))
		return ;
	if (s->save_head->prev == 0)
		clear_prompt(s);
	else
	{
		s->save_head = s->save_head->prev;
		move_cursor(s);
		if (s->input)
			free(s->input);
		s->input = 0;
		write(1, s->save_head->input, ft_strlen(s->save_head->input));
		s->input = ft_strdup(s->save_head->input);
	}
}

t_save	*push_front_save(char *input, t_save *old_head, int flag)
{
	t_save	*new;

	new = 0;
	if (!ft_calloc_m(1, sizeof(t_save), (void *)&new))
		exit(1);
	new->input = ft_strdup(input);
	new->prev = 0;
	new->next = old_head;
	new->flag = flag;
	if (old_head != 0)
		old_head->prev = new;
	return (new);
}

void	move_cursor(t_state *s)
{
	t_keypos	pos;
	int			len;

	if (s->input != 0)
		len = ft_strlen(s->input);
	else
		len = 0;
	set_cursor(&pos.col, &pos.row);
	pos.col -= len;
	if (pos.col < 0)
	{
		pos.row--;
		pos.col = s->max.col + pos.col;
	}
	tputs(tgoto(s->t.cm, pos.col, pos.row), 1, ft_putchar);
	tputs(tgetstr("ce", NULL), 1, ft_putchar);
}

void	press_up(t_state *s)
{
	if (!s->save_head)
		return ;
	if (s->input != 0 && s->s_flag == 0)
		s->save_head = push_front_save(s->input, s->save_head, 0);
	if ((s->save_head->next != 0 && s->s_flag != 0) || s->save_head->flag == 0)
		s->save_head = s->save_head->next;
	s->s_flag = 1;
	move_cursor(s);
	write(1, s->save_head->input, ft_strlen(s->save_head->input));
	if (s->input)
		free(s->input);
	s->input = ft_strdup(s->save_head->input);
}

char	*delete_last_char(char *str)
{
	char	*tmp;
	int		len;
	int		i;

	if (str == 0)
		return (0);
	len = ft_strlen(str);
	if (!ft_calloc_m(len, sizeof(char), (void *)&tmp))
		exit(1);
	i = 0;
	while (str[i + 1])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[len - 1] = '\0';
	free(str);
	if (ft_strlen(tmp) == 0)
	{
		free(tmp);
		tmp = 0;
	}
	str = tmp;
	return (str);
}

int		ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void	put_backspace(t_state *s)
{
	int	col;
	int	row;

	set_cursor(&col, &row);
	if (!s->input || (s->start.row >= row && s->start.col >= col))
		return ;
	col--;
	if (col < 0)
	{
		row -= 1;
		col = s->max.col;
	}
	tputs(tgoto(s->t.cm, col, row), 1, ft_putchar);
	tputs(s->t.ce, 1, ft_putchar);
	s->input = delete_last_char(s->input);
}

void	handle_eof(t_state *s, char *input)
{
	if (!input)
	{
		printf("exit\n");
		tcsetattr(STDIN_FILENO, TCSANOW, &s->t.save);
		exit(0);
	}
}

void	print_save_char(t_state *s, char c)
{
	s->input = ft_strcjoin(s->input, c);
	write(1, &c, 1);
}

int	ft_isprint(int c)
{
	return (32 <= c && c <= 126);
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}


void	handle_keycode(t_state *s, int keycode)
{
	if (keycode == 4)
		handle_eof(s, s->input);
	else if (keycode == 127)
		put_backspace(s);
	else if (keycode == 4283163)
		press_up(s);
	else if (keycode == 4348699)
		press_down(s);
	else
	{
		if (ft_isprint((char)keycode))
			print_save_char(s, (char)keycode);
	}
}

/* 현재 커서의 위치를 표준입력에 출력한다. */
void	init_set_cursor(char buf[255], int *read_ret, int *i, int *flag)
{
	write(0, "\033[6n", 4);
	*read_ret = read(0, buf, 254);
	if (*read_ret < 0)
		*read_ret = 0;
	buf[*read_ret] = '\0';
	*i = 0;
	*flag = 0;
}

int		get_nbr_len(int n)
{
	int	ret;

	ret = 0;
	while (n > 0)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

/* 현재 커서 위치를 받아오네? */
void	set_cursor(int *col, int *row)
{
	int		i;
	int		flag;
	char	buf[255];
	int		read_ret;

	init_set_cursor(buf, &read_ret, &i, &flag);
	while (buf[++i])
	{
		if ('0' <= buf[i] && buf[i] <= '9')
		{
			if (flag == 0)
				*row = ft_atoi(&buf[i]) - 1;
			else
			{
				*col = ft_atoi(&buf[i]) - 1;
				break ;
			}
			flag++;
			i += get_nbr_len(*row) - 1;
		}
	}
}
void	set_cursor_w(t_state *s)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	s->max.col = w.ws_col;
	s->max.row = w.ws_row;
	set_cursor(&s->start.col, &s->start.row);
}

t_history	*ft_lstlast_history(t_history *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_history(t_history **lst, t_history *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		(ft_lstlast_history(*lst))->next = new;
		new->prev = (ft_lstlast_history(*lst));
	}
}



int		term_loop(t_state *s)
{
	int c;

	set_cursor_w(s);
	set_cursor(&s->cur.col, &s->cur.row);
	c = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == '\n')
		{
			write(1, "\n", 1);
			return (0);
		}
		else
			handle_keycode(s, c);
		c = 0;
	}
	return (0);
}
/* noncanonical 로 바꿈 */
void	init_term(t_state *s)
{
	tcgetattr(STDIN_FILENO, &s->t.term);
	s->t.term.c_lflag &= ~ICANON;
	s->t.term.c_lflag &= ~ECHO;
	s->t.term.c_cc[VMIN] = 1;
	s->t.term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &s->t.term);
	tgetent(NULL, "xterm");
	s->t.cm = tgetstr("cm", NULL);
	s->t.ce = tgetstr("ce", NULL);
}

void	delete_save(t_save *save)
{
	if (save->prev != 0)
		save->prev->next = save->next;
	if (save->next != 0)
		save->next->prev = save->prev;
	free(save->input);
	free(save);
	save = 0;
}

void	reset_save(t_state *s)
{
	t_save	*tmp;

	if (s->save_head == 0)
		return ;
	while (s->save_head->prev)
		s->save_head = s->save_head->prev;
	tmp = s->save_head->next;
	if (s->save_head->flag == 0)
	{
		delete_save(s->save_head);
		s->save_head = tmp;
	}
	s->s_flag = 0;
}

void	get_str(t_state *s)
{
	print_dir();
	init_term(s);
	while (1)
	{
		if (term_loop(s) == 0)
		{
			reset_save(s);
			break;
		}
	}
}

t_history	*ft_lstnew_history(void *content)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	if (new == 0)
		return (0);
	new->content = content;
	new->next = 0;
	new->prev = 0;
	return (new);
}

void	init_state(t_state *state)
{
	ft_memset((void *)state, 0, sizeof(t_state));
	tcgetattr(0, &state->t.save);
}


void	free_2d(char **array)
{
	char	**temp;
	int		i;

	temp = array;
	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->av)
			free_2d(tmp->av);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	save_history(t_state *s)
{
	reset_save(s);
	if (s->input == 0)
		return ;
	if (s->save_head == 0)
	{
		s->save_head = push_front_save(s->input, 0, 1);
	}
	else
	{
		s->save_head = push_front_save(s->input, s->save_head, 1);
	}
}

void	prepare_token_and_cmd(t_state *state)
{
	// save_history(state);
	free_cmd(state->cmd_head);
	state->token_head = 0;
	state->cmd_head = 0;
	state->path_head = 0;
	//free(state->input);
	state->input = 0;
	reset_save(state);
}

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		if (g_state.is_fork == 0)
		{
			write(1, "\n", 1);
			print_dir();
			if (g_state.input)
				free(g_state.input);
			g_state.input = 0;
			g_state.ret = 1;
		}
		else
		{
			g_state.ret = 130;
			write(1, "\n", 1);
		}
	}
	else if (signo == SIGQUIT)
	{
		if (g_state.is_fork == 1)
		{
			g_state.ret = 131;
			write(1, "Quit: 3\n", 9);
		}
	}
}

int main(int ac, char **av, char **env)
{
    char	*input;
	char	*tokens;

	init_list(env);
	init_state(&g_state);
	signal(SIGINT, (void *)handle_signal);
	signal(SIGQUIT, (void *)handle_signal);
    while (1)
	{
		get_str(&g_state);
		tcsetattr(0, TCSANOW, &g_state.t.save);
		save_history(&g_state);
		if (return_syntax_error(g_state.input))
			free(g_state.input);
		else
		{
			tokens = tokenize(g_state.input);
			init_minishell(tokens, env);
		}
		prepare_token_and_cmd(&g_state);
    }
    return 0;
}
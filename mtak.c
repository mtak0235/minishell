#include "minishell.h"

int					ft_strncmp_env(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
	&& i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s1[i] != '=')
		return (1);
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* env 구현 */
void func_env()
{
	t_list *curr;

	curr = g_envlst;
	while (curr)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
	exit(EXIT_SUCCESS);
}

/* unset */
void func_unset(char *str)
{
	char *del_env;
	t_list *del_node;

	del_env = ft_strdup(str);
	if (!(del_node = search_env_address_return_prev(del_env, g_envlst)))
		return;
	del_next_node(del_node);
}

/* change dir */
int func_cd(char *dir)
{
	if (chdir(dir) == 0)
		return (1);
	else if (!*dir)
		exit(EXIT_SUCCESS);
	else
	{
		print_error_message("cd: ", dir);
		exit(EXIT_FAILURE);
	}	
	return (0);
}

/* 환경변수 치환해주는 함수*/
t_list	*search_env_address_return_prev(char *str, t_list *envlst)
{
	t_list *prev;

	prev = envlst;
	/* 어차피 처음 env2개는 수정 안하겠지...? */
	while (prev->next)
	{
		if (!ft_strncmp_env((char *)prev->next->content, str, ft_strlen(str)))
			return (prev);
		prev = prev->next;
	}
	return (NULL);
}

/* 환경변수 값 찾아서 리턴 */
char *get_env(char *str, t_list *envlst)
{
	t_list *tmp;
	char *ret;
	int i = 0;

	if (!(tmp = search_env_address_return_prev(str, envlst)))
		return (NULL);
	ret = ft_strdup((char *)tmp->next->content);
	while (ret[i])
		if (ret[i++] == '=')
			break;
	ret = ft_strdup(&ret[i]);
	return (ret);
}


void del_next_node(t_list *target)
{
	t_list *rm_node;

	rm_node = target->next;
	target->next = rm_node->next;
	free((char *)rm_node->content);
	free(rm_node);
}

void free_machine(char **strs)
{
	int i;
	i = 0;
	while (!strs[i])
		free(strs[i++]);
	free(strs);
}

int is_whitespace(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int is_exportformat(char *str)
{
	int i = 0;

	if (ft_isdigit(*str))
		return (0);
	while (str[i])
	{
		if (str[i] == '=' && is_whitespace(str[i - 1]) && is_whitespace(str[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

/* export*/
void func_export(char *str)
{
	char *new_env;
	t_list *node;
	char **tmp;

	if (!is_exportformat(str))
		return ;
	new_env = ft_strdup(str);

	tmp = ft_split(new_env, '=');
	if ((node = search_env_address_return_prev(tmp[0], g_envlst)))
		del_next_node(node);
	free_machine(tmp);

	node = ft_lstnew(new_env);
	ft_lstadd_back(&g_envlst, node);
}

/* export만 들어왔을 때 */
void only_export()
{
	t_list *curr;

	curr = g_envlst;
	while (curr->next)
	{
		printf("declare -x %s\n", (char *)curr->content);
		curr = curr->next;
	}
}

void free_lst(t_list *lst)
{
	t_list *curr;
	t_list *tmp;
	
	curr = lst;
	while (curr)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}
/* non builtin은 바로 처리 */
int is_builtin(char *cmd, char *av)
{
	if (!av && !ft_strncmp(cmd, "export", 6))
		only_export();
	else if (!ft_strncmp(cmd, "export", 6))
		func_export(av);
	else if (!ft_strncmp(cmd, "unset", 5))
		func_unset(av);
	else if (!ft_strncmp(cmd, "env" , 3) || !ft_strncmp(cmd, "ENV" , 3))
		func_env();
	else if (!ft_strncmp(cmd, "cd", 2))
		func_cd(av);
	else
		return (1);
	return (0);
}

/* init envlst */

void init_list(char **env)
{
	t_list *node;
	int i;
	char *tmp;

	tmp = ft_strdup(env[0]);
	g_envlst = ft_lstnew(tmp);
	i = 1;
	while (env[i])
	{
		tmp = ft_strdup(env[i++]);
		node = ft_lstnew(tmp);
		ft_lstadd_back(&g_envlst, node);
	}
}

 /* init history */
/*
void init_history()
{
	t_history *node;
	g_history = ft_lstnew_history(0);
} */
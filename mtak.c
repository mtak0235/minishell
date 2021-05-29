#include "minishell.h"


/* history */

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
}

/* unset */
void func_unset(char *str)
{
	char **tmp;
	char *del_env;
	t_list *del_node;

	tmp = ft_split(str, '=');
	del_env = ft_strdup(tmp[0]);
	free_machine(tmp);
	if (!(del_node = search_env_address_return_prev(del_env, g_envlst)))
		return;
	del_next_node(del_node);
}

/* change dir */
int func_cd(char *dir)
{
	if (chdir(dir))
		return (1);
	return (0);
}

/* 환경변수 치환해주는 함수*/
t_list	*search_env_address_return_prev(char *str, t_list *envlst)
{
	char *ret;
	t_list *prev;

	prev = envlst;
	/* 어차피 처음 env2개는 수정 안하겠지...? */
	while (prev->next)
	{
		if (!ft_strncmp((char *)prev->next->content, str, ft_strlen(str)))
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
	free(rm_node->content);
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
	/* 여기에 func_env출력하면 export한게 잘 뜨는데 그냥 env하면 안뜬다.또 그냥 export하면 안뜬다. 그냥 이 함수 안에서만 된다.   */
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

/* non builtin은 바로 처리 */
int is_builtin(char *cmd, char *av)
{
	if (!av && !ft_strncmp(cmd, "export", 6))
		only_export();
	else if (!ft_strncmp(cmd, "export", 6))
		func_export(av);
	else if (!ft_strncmp(cmd, "unset", 4))
		func_unset(av);
	else if (!ft_strncmp(cmd, "env" , 3))
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

	g_envlst = ft_lstnew(env[0]);
	i = 1;
	while (env[i])
	{
		node = ft_lstnew(env[i++]);
		ft_lstadd_back(&g_envlst, node);
	}
}
#include "mtak.h"

/* env 구현 */
void func_env(t_list *envlst)
{
	t_list *curr;

	curr = envlst;
	while (curr->next)
	{
		printf("%s\n", (char *)curr->content);
		curr = curr->next;
	}
}

//void ft_delnode()
/* unset */
void func_unset(char *str, t_list **envlst)
{
	char **tmp;
	char *del_env;
	t_list *del_node;

	tmp = ft_split(str, ' ');
	del_env = ft_strdup(tmp[1]);
	free_machine(tmp);
	if (!(del_node = search_env_address(del_env, *envlst)))
		return;
	//삭제할 노드만 있는데 어떻게 잘 이어붙이지?
}

/* change dir */
int change_dir(char *dir)
{
	if (chdir(dir))
		return (1);
	return (0);
}

/* 환경변수 치환해주는 함수*/
t_list *search_env_address(char *str, t_list *envlst)
{
	char *ret;
	t_list *curr;

	curr = envlst;
	while (curr->next)
	{
		if (ft_strncmp((char *)curr->content, str, ft_strlen(str)))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char *get_env(char *str, t_list *envlst)
{
	t_list *tmp;
	char *ret;
	int i = 0;

	if (!(tmp = search_env_address(str, envlst)))
		return (NULL);
	ret = ft_strdup((char *)tmp->content);
	while (ret[i])
		if (ret[i++] == '=')
			break;
	ret = ft_strdup(ret[i]);
	return (ret);
}

void init_list(t_list **head, char **env)
{
	t_list *node;
	int i;

	*head = ft_lstnew(env[0]);
	i = 1;
	while (env[i])
	{
		node = ft_lstnew(env[i++]);
		ft_lstadd_back(head, node);
	}
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

void free_machine(char **strs)
{
	int i;
	i = 0;
	while (!strs[i])
		free(strs[i++]);
	free(strs);
}

/* export 구현 */
void	func_export(char *str, t_list **envlst)
{
	char **tmp;
	char *new_env;
	t_list *new_node;

	tmp = ft_split(str, ' ');
	if (!is_exportformat(tmp[1]))
		return (free_machine(tmp));
	new_env = ft_strdup(tmp[1]);
	free_machine(tmp);
	if (search_env_address(new_env, *envlst))
		return;
	ft_lstadd_back(envlst, new_node);
}

/* export만 들어왔을 때 */
void only_export(t_list *envlst)
{
	t_list *curr;

	curr = envlst;
	while (curr->next)
	{
		printf("declare -x %s\n", (char *)curr->content);
		curr = curr->next;
	}
}
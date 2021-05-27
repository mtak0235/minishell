#include "mtak.h"

/* 환경변수 치환해주는 함수
인풋 char *
리턴 char * */

void add_node(t_envlst *target, char *data)
{
	t_envlst *node;

	node = (t_envlst *)malloc(sizeof(t_envlst));
	node->next = target->next;
	node->data = data;
	target->next = node;
}

void *init_envlst(t_envlst *head, char **env)
{
	t_envlst *node;
	int i;

	head = (t_envlst *)malloc(sizeof(t_envlst));
	head->data = env[0];
	head->next = NULL;
	node = head;
	i = 1;
	while (env[i])
	{
		add_node(node, env[i++]);
		node = node->next;
	}
}

void	func_export(char *str, t_envlst *envlst)
{
	t_envlst *bottom;

	bottom = envlst;
	while (bottom->next)
		bottom = bottom->next; 
	//add_node(bottom, str);
}
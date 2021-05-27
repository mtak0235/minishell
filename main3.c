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

t_history	*create_new_node(char *line)
{
	t_history *res = malloc(sizeof(t_history));
	res->val = line;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

t_history *insert_at_head(t_history **head, t_history *node_to_insert)
{
	node_to_insert->next = *head;
	if (*head != NULL)
		(*head)->prev = node_to_insert;
	*head = node_to_insert;
	node_to_insert->prev = NULL;
	return (node_to_insert);
}

void	insert_after_node(t_history *node_to_insert_after, t_history *newnode)
{
	newnode->next = node_to_insert_after->next;
	if (newnode->next != NULL)
		newnode->next->prev = node_to_insert_after;
	newnode->prev = node_to_insert_after;
	node_to_insert_after->next = newnode;
}

void	remove_node(t_history **head, t_history *node_to_remove)
{
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		if (*head != NULL)
			(*head)->prev = NULL;
	}
	else
	{
		node_to_remove->prev->next = node_to_remove->next;
		if (node_to_remove->next != NULL)
			node_to_remove->next->prev = node_to_remove->prev;
	}
	node_to_remove->next = NULL;
	node_to_remove->prev = NULL;
	return ;
}

void	init_minishell(t_main *main)
{
	main->history.val = NULL;
	main->history.prev = NULL;
	main->history.next = NULL;
}

void	init_shell(void)
{
	printf("-----------------------------------------\n");
	printf("------Napark & Seokim's Micro Shell------\n");
	printf("--------------Enjoy It!------------------\n");
	printf("-----------------------------------------\n");
}

int	main(int ac, char *av[], char *env[])
{
	t_main	main;
	t_history *head;
	pid_t	pid;
	struct stat buffer;
	int	status;
	char *line;
	char	buf[256];

	init_minishell(&main);
	//while (1)
	//{
	//	get_next_line(&line);
	//	printf("%s\n", line);
	//}
	//while (env[i])
	//	printf("%s\n", env[i++]);
	int fd[2];
	int fd2;
	int ret;

	fd2 = open("test.txt", O_WRONLY);
	char *args[3];
	args[0] = ft_strdup("/bin/echo");
	args[1] = ft_strdup("muyaho");
	args[2] = 0;
	init_shell();

	while (1)
	{
		getcwd(buf, sizeof(buf));
		printf("%s\n", buf);
		get_next_line(&line);
		//pid = fork();
		//if (pid == 0)
		//{
		//	//pipe(fd);
		//	ret = execve(args[0],args, env);
		//	exit(ret);
		//}

		//printf("%s\n", getenv("PATH"));
		//else if (pid > 0)
		//{
		//	waitpid(pid, 0, 0);
		//}
		//chdir(line);
		//if (main.history.val == NULL)
		//	main.history = *create_new_node(line);
		//else
		//	insert_after_node(head, create_new_node(line));
		//printf("--------------------\n");
		//printf("%s\n", main.history.val);
		//getcwd(buf, sizeof(buf));
		//printf("%s\n",buf);
		//status = stat("/Users/seonja/Documents/minishell/test/a.txt", &buffer);
		//printf("%d\n, %u\n", status, buffer.st_uid);
	}

}
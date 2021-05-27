#ifndef MTAK_H
# define MTAK_H

#include "libft/libft.h"
#include <stdio.h>
# include <unistd.h>

typedef struct s_envlst
{
	char *data;
	struct s_envlst *next;
}				t_envlst;

void add_node(t_envlst *target, char *data);
void init_envlst(t_envlst *head, char **env);
void	func_export(char *str, t_envlst *envlst);


#endif
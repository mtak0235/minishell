#ifndef MTAK_H
# define MTAK_H

#include "./libft/libft.h"
#include <stdio.h>
# include <unistd.h>


void add_node(t_list *target, char *data);
void init_list(t_list **head, char **env);
void	func_export(char *str, t_list **envlst);


#endif
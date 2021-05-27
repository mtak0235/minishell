#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft/libft.h"

# define DOUBLE 1
# define SINGLE 2

typedef	struct s_history
{
	char			*val;
	struct s_history *prev;
	struct s_history *next;
}				t_history;

typedef struct s_command
{
	int			flags;
	int			quote;
	char		*arg;
}				t_command;

typedef struct s_main
{
	t_history history;
	t_command command;
}				t_main;

#endif

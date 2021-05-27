#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_input
{
	char		**input;
	char		*val;
	struct s_input *prev;
	struct s_input *next;
}				t_input;

int	main(int ac, char **av, char **envp)
{
	t_input input;
	int		i;
	char	*tmp;
	char	*save;

	i = 0;
	save = (void *)0;

	while (++i < ac)
	{
		printf("%s\n", av[i]);
	}
	printf("-----------------");
	i = 0;
	while (++i < ac)
	{
		if ((i + 1) < ac)
			tmp = ft_strjoin(av[i], " ");
		else
			tmp = ft_strdup(av[i]);
		if (save == (void *)0)
			save = ft_strdup(tmp);
		else
		{
			save = ft_strjoin(input.val, tmp);
			free(input.val);
		}
		free(tmp);
		input.val = save;
	}
	printf("%s\n", input.val);
	input.input = ft_split(input.val, ' ');
	i = 0;
	while (input.input[i])
	{
		printf("%s\n", input.input[i]);
		i++;
	}
	free(input.val);
}
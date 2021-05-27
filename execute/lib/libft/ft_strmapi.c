/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:03:22 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 16:03:34 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Applies 'f' to each character of 's' to create a new string (with malloc)
**   resulting from successive applications of 'f'.
** - Returns the string created from the successive applications of 'f',
**   or returns NULL if the allocation fails.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	size;
	char	*res;

	if (s == NULL)
		return (NULL);
	size = ft_strlen(s);
	res = ft_calloc(size + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

/*
** line 32-33 : Added protection
*/

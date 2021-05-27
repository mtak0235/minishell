/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:58:31 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 15:58:47 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Locates 'first' occurrence of 'c'(converted to a char) pointed to by 's'.
** - The terminating NULL is considered to be part of string.
**   (therefore if 'c' is '', the functions locate terminating '')
** - Returns a pointer to the located character,
**   or NULL if the character does not appear in the string.
*/

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	if (s == 0)
		return (0);
	i = 0;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

/*
** line 28-29 : add condition if 'c' is 0, to return a pointer
**              to the terminating-Null of 's'
** line 33 : change return value from 's' to 's + i'
**
** Simpler Code : return (ft_memchr(s, c, ft_strlen(s) + 1);
*/

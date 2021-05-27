/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:00:17 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 16:00:32 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Allocates sufficient memory for a copy of the string
** - Does the copy
** - Returns a pointer to it
**   If insufficient memory is available, NULL is returned
*/

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s1);
	dup = ft_calloc(size + 1, 1);
	if (dup == NULL)
		return (NULL);
	ft_memcpy(dup, s1, size);
	dup[size] = 0;
	return (dup);
}

/*
** line 29-30 : Added protection
*/

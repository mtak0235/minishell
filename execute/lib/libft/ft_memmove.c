/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:52:35 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 15:52:55 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Copies 'len' bytes from string 'src' to 'dst'.
** - The two strings may overlap (i.e. src+5, src)
**   copy is always done in a non-destructive manner.
** - Returns original value of dst.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *usrc;
	unsigned char *udst;
	unsigned char temp[len];

	if (dst == NULL && src == NULL)
		return (NULL);
	usrc = (unsigned char *)src;
	udst = (unsigned char *)dst;
	ft_memcpy(temp, usrc, len);
	ft_memcpy(udst, temp, len);
	return (dst);
}

/*
** line 28-29 : Added protection
*/

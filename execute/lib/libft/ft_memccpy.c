/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:48:28 by napark            #+#    #+#             */
/*   Updated: 2021/04/28 18:13:51 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Copies bytes from string 'src' to string 'dst'.
** - Stops copying when 'c' converted to an unsigned char occurs in 'src'
** - Returns a pointer to the byte after the copy of c in 'dst',
**   otherwise, returns a NULL pointer after n bytes are copied
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	int				occured;
	unsigned char	*usrc;

	usrc = (unsigned char *)src;
	i = 0;
	occured = 0;
	while (i < n && usrc[i] && !occured)
	{
		occured = ((usrc)[i] == (unsigned char)c) ? 1 : 0;
		i++;
	}
	if (occured)
	{
		ft_memcpy(dst, usrc, i);
		return (dst + i);
	}
	else
	{
		ft_memcpy(dst, usrc, n);
		return (0);
	}
}

/*
** line 31 : add while condition 'i < n', preventioning from over searching.
*/

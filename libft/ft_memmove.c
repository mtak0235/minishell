/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 15:53:51 by seokim            #+#    #+#             */
/*   Updated: 2021/01/02 00:12:06 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	i = 0;
	if (dest == src || n == 0)
		return (dest);
	if (dest < src)
	{
		tmp_dest = (unsigned char *)dest;
		tmp_src = (unsigned char *)src;
		while (n--)
			*tmp_dest++ = *tmp_src++;
	}
	else
	{
		tmp_dest = (unsigned char *)dest + (n - 1);
		tmp_src = (unsigned char *)src + (n - 1);
		while (n--)
			*tmp_dest-- = *tmp_src--;
	}
	return (dest);
}

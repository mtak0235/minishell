/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:21:10 by seokim            #+#    #+#             */
/*   Updated: 2020/12/28 13:02:26 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*psrc;

	dest = (unsigned char *)dst;
	psrc = (const unsigned char *)src;
	if (!n || dst == src)
		return (dst);
	while (n > 0)
	{
		*dest = *psrc;
		dest++;
		psrc++;
		n--;
	}
	return (dst);
}

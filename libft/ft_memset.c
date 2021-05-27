/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 10:09:03 by seokim            #+#    #+#             */
/*   Updated: 2020/12/24 10:16:38 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char chr;
	unsigned char *str;

	chr = (unsigned char)c;
	str = (unsigned char *)s;
	while (n > 0)
	{
		*str = chr;
		str++;
		n--;
	}
	return (s);
}

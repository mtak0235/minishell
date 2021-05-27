/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 21:44:27 by seokim            #+#    #+#             */
/*   Updated: 2021/01/04 19:03:06 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_calloc(size_t num, size_t size)
{
	void				*pnt;
	void				*res;
	unsigned long long	len;

	len = num * size;
	if (!(pnt = malloc(len)))
		return (NULL);
	res = pnt;
	while (len--)
		*(char *)pnt++ = '\0';
	return (res);
}

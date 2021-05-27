/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 19:35:26 by seokim            #+#    #+#             */
/*   Updated: 2020/12/26 19:56:03 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *ps1;
	const unsigned char *ps2;

	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;
	while (n > 0 && *ps1 == *ps2)
	{
		ps1++;
		ps2++;
		n--;
	}
	return (n ? *ps1 - *ps2 : 0);
}

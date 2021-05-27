/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:28:54 by seokim            #+#    #+#             */
/*   Updated: 2020/12/28 19:25:14 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int len;

	len = ft_strlen(s) - 1;
	if ((char)c == '\0')
		return ((char *)s + (len + 1));
	while (0 <= len)
	{
		if (((char *)s)[len] == c)
			return ((char *)(s + len));
		len--;
	}
	return (NULL);
}

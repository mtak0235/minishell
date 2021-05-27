/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:44:54 by seokim            #+#    #+#             */
/*   Updated: 2020/12/27 02:15:32 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int i;

	i = 0;
	if (!ft_strlen(to_find))
		return ((char *)str);
	while (*str && len)
	{
		if (*str == *to_find)
		{
			while (i < len && str[i] == to_find[i])
			{
				i++;
				if (!to_find[i])
					return ((char *)str);
			}
		}
		str++;
		len--;
	}
	return (0);
}

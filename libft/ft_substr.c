/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:34:40 by seokim            #+#    #+#             */
/*   Updated: 2021/01/04 19:49:02 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*arr;
	unsigned int	i;

	i = 0;
	if (!s || !(arr = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	if (!*s || ft_strlen(s) <= start)
		return (arr);
	s += start;
	while (len--)
		arr[i++] = *s++;
	arr[i] = '\0';
	return (arr);
}

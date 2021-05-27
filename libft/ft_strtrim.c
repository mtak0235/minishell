/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 00:04:52 by seokim            #+#    #+#             */
/*   Updated: 2020/12/29 16:58:17 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_set(char s1, char const *s2)
{
	while (*s2)
	{
		if (s1 == *s2)
			return (1);
		s2++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*arr;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (!s1)
		return (NULL);
	j = ft_strlen(s1) - 1 - i;
	while (s1[i] && ft_set(s1[i], set))
		i++;
	while (i < j && ft_set(s1[j], set))
		j--;
	if (!(arr = (char *)malloc(sizeof(char) * (j - i + 2))))
		return (NULL);
	while (i <= j)
	{
		arr[k++] = s1[i++];
	}
	arr[k] = '\0';
	return (arr);
}

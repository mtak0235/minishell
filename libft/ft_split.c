/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:38:33 by seokim            #+#    #+#             */
/*   Updated: 2021/01/18 17:24:38 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_dim(char const *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		while (*s != c && *s)
			s++;
		i++;
	}
	return (i);
}

char		*ft_copy(char const *s, int len)
{
	char	str[len + 1];
	char	*arr;
	int		i;

	i = 0;
	arr = (char *)s;
	while (i < len)
	{
		str[i] = arr[i];
		i++;
	}
	str[i] = 0;
	return (ft_strdup(str));
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		dime;
	char	**str;
	char	*arr;

	i = 0;
	if (!s)
		return (0);
	dime = ft_dim(s, c);
	if (!(str = (char**)malloc(sizeof(char*) * (dime + 1))))
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		arr = (char *)s;
		while (*s != c && *s)
			s++;
		str[i++] = ft_copy(arr, s - arr);
	}
	str[i] = 0;
	return (str);
}

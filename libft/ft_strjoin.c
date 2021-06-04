/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:55:03 by seokim            #+#    #+#             */
/*   Updated: 2021/06/01 14:08:59 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	int		total;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(arr = (char *)malloc(sizeof(char) * total)))
		return (NULL);
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	while (s2[j])
		arr[i++] = s2[j++];
	arr[i] = '\0';
	return (arr);
}

void	*ft_memset_m(void *ptr, int val, size_t n)
{
	unsigned char	*tmp_ptr;
	unsigned char	tmp_val;
	size_t			i;

	tmp_ptr = ptr;
	tmp_val = val;
	i = 0;
	while (i < n)
	{
		tmp_ptr[i] = tmp_val;
		i++;
	}
	return (ptr);
}

int	ft_calloc_m(size_t n, size_t size, void **ret)
{
	*ret = (char *)malloc(size * n);
	if (!*ret)
		return (0);
	ft_memset_m(*ret, 0, (n * size));
	return (1);
}

char	*ft_strcjoin(char *str, char c)
{
	char	*ret;
	int		i;

	if (!str)
	{
		if (!ft_calloc_m(2, sizeof(char), (void *)&ret))
			exit(1);
		ret[0] = c;
		ret[1] = '\0';
	}
	else
	{
		if (!ft_calloc_m(ft_strlen(str) + 2, sizeof(char), (void *)&ret))
			exit(1);
		i = -1;
		while (str[++i])
			ret[i] = str[i];
		ret[i] = c;
		ret[i + 1] = '\0';
		free(str);
	}
	return (ret);
}

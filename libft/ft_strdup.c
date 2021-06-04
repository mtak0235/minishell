/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 22:08:01 by seokim            #+#    #+#             */
/*   Updated: 2021/06/01 13:22:38 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(char *src)
{
	char	*arr;
	int		i;

	i = 0;
	if (!(arr = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1))))
		return (NULL);
	while (src[i] != '\0')
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char		*ft_strndup_m(char *src, int size)
{
	char	*arr;
	int		i;

	i = 0;
	if (!(arr = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (src[i] != '\0' && i < size)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

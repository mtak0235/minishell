/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:17:33 by seokim            #+#    #+#             */
/*   Updated: 2021/01/03 00:49:56 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrev(char *str)
{
	int			i;
	int			j;
	char		tmp;

	i = ft_strlen(str) - 1;
	j = 0;
	while (str[j] == '-')
		j++;
	while (j < i)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		j++;
		i--;
	}
	return (str);
}

int				ft_numlen(int n)
{
	int			i;
	long		ln;

	i = 0;
	ln = (long)n;
	if (n < 0)
	{
		ln = (long)n * -1;
		i++;
	}
	else if (n == 0)
		i = 1;
	while (ln > 0)
	{
		ln /= 10;
		i++;
	}
	return (i);
}

int				ft_nbr(char *str, int n, int j)
{
	int			loop;
	long		ln;

	loop = 1;
	ln = (long)n;
	while (loop)
	{
		if (ln < 0)
		{
			str[j++] = '-';
			ln = ln * -1;
		}
		else if (ln < 10)
		{
			str[j++] = ln + '0';
			loop = 0;
		}
		else
		{
			str[j++] = (ln % 10) + '0';
			ln = ln / 10;
		}
	}
	return (j);
}

char			*ft_itoa(int n)
{
	char		*str;
	char		*arr;
	int			i;
	int			j;

	i = ft_numlen(n);
	j = 0;
	if (!(arr = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	j = ft_nbr(arr, n, j);
	arr[j] = '\0';
	str = ft_strrev(arr);
	return (str);
}

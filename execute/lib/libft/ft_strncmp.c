/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:03:57 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 16:04:10 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Compares 's1' and 's2' in lexicographical order,
**   but not more than 'n' characters.
** - Characters that appear after a `\0' character are not compared.
**   (since strncmp() is designed for comparing strings rather than binary data)
** - Comparison is done in format of 'unsigned characters',
**   so `\200' is greater than `\0'
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
** line 31 : cast return value into 'unsigned char' as manual says
** line 34 : change return value from 's1[i] - s2[i]' to 0.
**			 (since comparision should be stopped after Null appears)
*/

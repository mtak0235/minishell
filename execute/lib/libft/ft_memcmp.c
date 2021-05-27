/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:49:46 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 15:50:04 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Compares 's1' against 's2', both strings are assumed 'n' bytes long.
** - Returns 0 if the two strings are identical or if n is 0.
**   (because zero-length strings are also always identical)
**   Otherwise, returns difference between the first two differing bytes.
**   (treated as unsigned char values, i.e. '200' is greater than '').
*/

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	if (n == 0)
		return (0);
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	i = 0;
	while (i < n - 1)
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (us1[i] - us2[i]);
}

/*
** line 34 : changed while condition from 'i < n'  to 'i < n - 1'
**           (n may include terminated-null.)
** line 34 : changed while condtion from '&& us1[i] && us2[i]'
**           to none, since the function stopped at \0
*/

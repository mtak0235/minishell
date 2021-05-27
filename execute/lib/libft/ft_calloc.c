/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:34:55 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 15:35:18 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Contiguously allocates enough space for 'count' objects
**   that are 'size' bytes of memory each.
** - The allocated memory is filled with bytes of value zero.
** - Returns a pointer to the allocated memory.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	res = (void *)malloc(count * size);
	if (res == 0)
		return (0);
	ft_memset(res, 0, count * size);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:34:24 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 15:34:40 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Writes 'n' zeroed bytes to the string 's'.
** - Does nothing if 'n' is zero.
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:04:27 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 18:32:50 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *s1, size_t size)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (dup == 0)
		return (0);
	ft_strcpy(dup, s1, size);
	dup[size] = 0;
	return (dup);
}

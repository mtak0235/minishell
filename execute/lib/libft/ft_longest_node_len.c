/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longest_node_len.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:41:36 by napark            #+#    #+#             */
/*   Updated: 2021/04/11 15:42:07 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_longest_node_len(t_list *lst)
{
	int max;

	max = -1;
	while (lst)
	{
		if (max < ft_strlen((char *)lst->content))
			max = ft_strlen((char *)lst->content);
		lst = lst->next;
	}
	return (max);
}

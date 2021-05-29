/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:42:28 by napark            #+#    #+#             */
/*   Updated: 2021/05/29 15:56:24 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/*
** - Adds the element 'new' at the end of the list
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
		(ft_lstlast(*lst))->next = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtak <mtak@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:21:45 by seokim            #+#    #+#             */
/*   Updated: 2021/06/01 13:18:10 by mtak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newls;

	if (!(newls = malloc(sizeof(t_list))))
		return (NULL);
	newls->content = content;
	newls->next = NULL;
	return (newls);
}

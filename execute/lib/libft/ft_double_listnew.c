/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_listnew.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: napark <napark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:42:04 by napark            #+#    #+#             */
/*   Updated: 2021/05/23 19:34:36 by napark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_double_list    *ft_double_lstnew(void *data)
{
    t_double_list       *node;

    node = malloc(sizeof(t_double_list));
    if (node == NULL)
        return (0);
    node->next = NULL;
    node->prev = NULL;
    node->data = data;
    return (node);
}
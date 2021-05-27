/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:14:51 by seokim            #+#    #+#             */
/*   Updated: 2020/12/30 01:50:53 by seokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long ln;

	ln = (long)n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ln = (long)n * -1;
	}
	if (ln < 10)
	{
		ft_putchar_fd(ln + '0', fd);
	}
	else
	{
		ft_putnbr_fd((ln / 10), fd);
		ft_putchar_fd((ln % 10) + '0', fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 20:01:23 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/07 20:49:37 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		n = 147483648;
		i += ft_putchar_fd('-', fd);
		i += ft_putchar_fd('2', fd);
	}
	if (n < 0)
	{
		i += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += ft_putnbr_fd(n % 10, fd);
	}
	else
		i += ft_putchar_fd(n + '0', fd);
	return (i);
}

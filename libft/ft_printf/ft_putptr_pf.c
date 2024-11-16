/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:31:53 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/01 21:34:25 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_writeptr(unsigned long long n)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_writeptr(n / 16);
		count += ft_writeptr(n % 16);
	}
	else
	{
		if (n <= 9)
		{
			ft_putchar_pf(n + 48);
			count++;
		}
		else
		{
			ft_putchar_pf(n + 87);
			count++;
		}
	}
	return (count);
}

int	ft_putptr_pf(unsigned long long ptr)
{
	int	p_len;

	p_len = 2;
	ft_writecheck_pf(write(1, "0x", 2));
	if (ptr == 0)
	{
		ft_writecheck_pf(write(1, "0", 1));
		p_len += 1;
	}
	else
		p_len += ft_writeptr(ptr);
	return (p_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:28:01 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/02 19:29:30 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_writehex(unsigned int n, const char format)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_writehex(n / 16, format);
		count += ft_writehex(n % 16, format);
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
			if (format == 'x')
				ft_putchar_pf(n + 87);
			if (format == 'X')
				ft_putchar_pf(n + 55);
			count++;
		}
	}
	return (count);
}

int	ft_puthex_pf(unsigned int hex, const char format)
{
	int	p_len;

	p_len = 0;
	if (hex == 0)
	{
		ft_writecheck_pf(write(1, "0", 1));
		p_len += 1;
	}
	else
		p_len += ft_writehex(hex, format);
	return (p_len);
}

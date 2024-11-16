/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:26:52 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/02 22:28:03 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_pf(va_list args, const char format)
{
	int	p_len;

	p_len = 0;
	if (format == 'c')
		p_len += ft_putchar_pf(va_arg(args, int));
	else if (format == 's')
		p_len += ft_putstr_pf(va_arg(args, char *));
	else if (format == 'p')
		p_len += ft_putptr_pf(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		p_len += ft_putnbr_pf(va_arg(args, int));
	else if (format == 'u')
		p_len += ft_putunsigned_pf(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		p_len += ft_puthex_pf(va_arg(args, unsigned int), format);
	else if (format == '%')
		p_len += ft_putchar_pf(format);
	return (p_len);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		p_len;
	va_list	args;

	i = 0;
	p_len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			p_len += ft_format_pf(args, str[i + 1]);
			i++;
		}
		else if (str[i] == '%' && str[i + 1] == '\0')
			break ;
		else
			p_len += ft_putchar_pf(str[i]);
		i++;
	}
	va_end(args);
	if (ft_writecheck_pf(0) < 0)
		return (-1);
	return (p_len);
}

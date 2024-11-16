/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_pf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:58:38 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/02 20:58:43 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned_pf(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_putunsigned_pf(n / 10);
		count += ft_putunsigned_pf(n % 10);
	}
	else
	{
		ft_putchar_pf(n + 48);
		count++;
	}
	return (count);
}

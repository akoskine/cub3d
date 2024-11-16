/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:30:58 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/01 17:31:31 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	get_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static	void	get_str(int size, int mode, int n, char *str)
{
	while (size > mode)
	{
		str[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

static char	*ft_itoa_pf(int n)
{
	int		size;
	int		mode;
	char	*str;

	mode = 0;
	size = get_size(n);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		n = 147483648;
		mode = 2;
	}
	if (n < 0)
	{
		str[0] = '-';
		mode = 1;
		n = -n;
	}
	get_str(size, mode, n, str);
	str[size] = '\0';
	return (str);
}

int	ft_putnbr_pf(int n)
{
	char	*str;
	int		p_len;

	p_len = 0;
	str = ft_itoa_pf(n);
	p_len = ft_putstr_pf(str);
	free(str);
	return (p_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:30:16 by akoskine          #+#    #+#             */
/*   Updated: 2022/12/09 16:40:18 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_itoa(int n)
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

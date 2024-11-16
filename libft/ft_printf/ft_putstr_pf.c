/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:56:24 by akoskine          #+#    #+#             */
/*   Updated: 2023/03/01 17:01:36 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_pf(char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
	{
		ft_writecheck_pf(write(1, "(null)", 6));
		return (6);
	}
	while (s[i] != '\0')
		i++;
	ft_writecheck_pf(write(1, s, i));
	return (i);
}

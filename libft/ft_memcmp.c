/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:59:51 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 16:18:44 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*tmp_s1;
	const unsigned char	*tmp_s2;
	size_t				i;

	i = 0;
	tmp_s1 = (const unsigned char *)s1;
	tmp_s2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (tmp_s1[i] != tmp_s2[i])
			return (tmp_s1[i] - tmp_s2[i]);
		i++;
	}
	return (0);
}

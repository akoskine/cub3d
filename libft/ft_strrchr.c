/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 17:44:49 by akoskine          #+#    #+#             */
/*   Updated: 2023/09/06 16:19:47 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		count;
	char	*ret;

	i = 0;
	count = 0;
	ret = (char *)s;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			count = i;
		i++;
	}
	if ((char)c == '\0')
		return (ret + i);
	if (count == 0 && s[0] != (char)c)
		return (0);
	return (ret + count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:25:45 by akoskine          #+#    #+#             */
/*   Updated: 2022/12/27 16:31:57 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*s;
	size_t	i;
	size_t	res;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	res = 0;
	if ((dst && dstsize < ft_strlen(dst)) || !dstsize)
		return (ft_strlen(src) + dstsize);
	s = (char *)src;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(s);
	if (dstsize > dst_len)
		res = src_len + dst_len;
	else
		res = src_len + dstsize;
	while (s[i] && (dst_len + 1) < dstsize)
	{
		dst[dst_len] = s[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
	return (res);
}

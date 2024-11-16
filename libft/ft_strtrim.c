/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:34:30 by akoskine          #+#    #+#             */
/*   Updated: 2022/12/08 23:17:14 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	set_check(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*start;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && set_check(s1[i], set))
		i++;
	start = (char *)&s1[i];
	j = ft_strlen(s1) - 1;
	while (j >= 0 && set_check(s1[j], set))
		j--;
	if ((j - i + 2) >= 0)
		res = malloc(sizeof(char) * (j - i + 2));
	if ((j - i + 2) < 0)
		res = malloc(sizeof(char) * 2);
	if (!res)
		return (NULL);
	ft_strlcpy(res, start, (j - i + 2));
	return (res);
}

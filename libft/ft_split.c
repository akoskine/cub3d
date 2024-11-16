/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 23:41:29 by akoskine          #+#    #+#             */
/*   Updated: 2023/01/02 23:44:21 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (j);
}

static int	ft_word_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

static void	ft_free_all(char **arr, int j)
{
	while (j >= 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	arr = (char **)malloc((ft_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (j < ft_words(s, c))
	{
		while (s[i] == c)
			i++;
		arr[j] = ft_substr(s, i, ft_word_len(s, c, i));
		if (!arr[j])
		{
			ft_free_all(arr, j);
			return (NULL);
		}
		i = i + ft_word_len(s, c, i);
		j++;
	}
	arr[j] = 0;
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:02:12 by akoskine          #+#    #+#             */
/*   Updated: 2023/04/10 17:55:42 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_static_str_read(char *static_str, int fd)
{
	int		read_size;
	char	*buffer;

	read_size = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(static_str, '\n') && read_size != 0)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_size] = '\0';
		static_str = ft_static_str_check(static_str);
		static_str = ft_strjoin_gnl(static_str, buffer);
	}
	free(buffer);
	return (static_str);
}

char	*ft_get_new_line(char *static_str)
{
	int		i;
	char	*new;

	i = 0;
	if (!static_str[i])
		return (NULL);
	while (static_str[i] && static_str[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (static_str[i] && static_str[i] != '\n')
	{
		new[i] = static_str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_get_new_static_str(char *static_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (static_str[i] && static_str[i] != '\n')
		i++;
	if (!static_str[i])
	{
		free(static_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(static_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (static_str[i])
		str[j++] = static_str[i++];
	str[j] = '\0';
	free(static_str);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*static_str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	static_str = ft_static_str_read(static_str, fd);
	if (!static_str)
		return (NULL);
	new_line = ft_get_new_line(static_str);
	static_str = ft_get_new_static_str(static_str);
	return (new_line);
}

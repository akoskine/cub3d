/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:49:58 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:04:05 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_rows_2d_map(t_game *game, int fd2)
{
	int		i;
	int		row_len;
	char	*line;

	i = 0;
	while (i < game->data->rows)
	{
		game->data->map[i] = (char *)dmh(game, sizeof(char )
				* (game->data->width + 1), NULL);
		if (!game->data->map[i])
			clean_exit(game, "Allocation of 2d map failed.", 1);
		line = dmh(game, 0, get_next_line(fd2));
		if (line == NULL)
			break ;
		ft_strlcpy(game->data->map[i], line, ft_strlen(line) + 1);
		row_len = ft_strlen(line);
		while (row_len < game->data->width)
			game->data->map[i][row_len++] = ' ';
		game->data->map[i][row_len] = '\0';
		i++;
	}
	game->data->map[i] = NULL;
}

void	create_2d_map(t_game *game, int fd2)
{
	int		i;
	char	*line;

	i = 0;
	while (i < game->data->map_start_point)
	{
		line = dmh(game, 0, get_next_line(fd2));
		i++;
	}
	game->data->map = (char **)dmh(game, sizeof(char *)
			* (game->data->rows + 1), NULL);
	if (!game->data->map)
		clean_exit(game, "Allocation of 2d map failed.", 1);
	add_rows_2d_map(game, fd2);
}

void	get_map_size(t_game *game, int fd)		// liian pitka
{
	char	*line;
	int		map_started;
	int		line_len;

	map_started = 0;
	while (1)
	{
		line = dmh(game, 0, get_next_line(fd));
		if (line == NULL)
			break ;
		if (line[0] == '\0')
		{
			game->data->map_start_point += 1;
			if (game->data->width > 0)
				map_started = 1;
			continue ;
		}
		if (map_started)
			clean_exit(game, "Empty line in map.", 1);
		line_len = ft_strlen(line);
		if (line_len > game->data->width)
			game->data->width = line_len;
		game->data->rows += 1;
	}
}

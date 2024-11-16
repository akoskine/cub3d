/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_information.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:50:08 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:08:10 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_rgb(t_game *game, char *line, int count, int idx)
{
	int		rgb[3];
	char	*tmp;

	while (*line != '\0' && idx != 3)
	{
		while (line[count] != ',' && line[count] != '\0')
			count++;
		tmp = dmh(game, 0, ft_strndup(line, count));
		if (tmp == NULL)
			clean_exit(game, "Allocation of tmp failed.", 1);
		rgb[idx] = ft_atoi(tmp);
		if (rgb[idx] < 0 || rgb[idx] > 255)
			clean_exit(game, "RGB color not in correct range (0-255).", 1);
		idx += 1;
		if (line[count] == '\0' || idx == 3)
			break ;
		line += count + 1;
		count = 0;
	}
	if (idx != 3 || line[count] != '\0')
		clean_exit(game, "RGB definition incorrect.", 1);
	return (0 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	add_color(t_game *game, char *line, int *xx_uint)
{
	int	i;

	line = dmh(game, 0, ft_strtrim(line, " "));
	if (!line)
		clean_exit(game, "Allocation failed at trimming line.", 1);
	if (*xx_uint != 0)
		clean_exit(game, "Same color already defined.", 1);
	if (ft_strchr(line, ' ') != NULL || ft_strchr(line, '\t') != NULL)
		clean_exit(game, "Color definition contains spaces or tabs.", 1);
	i = 0;
	while (line[i] != '\0')
	{
		if ((!ft_isdigit(line[i]) && line[i] != ','
				&& line[i] != '\0') || line[0] == ',')
			clean_exit(game, "RGB definition incorrect.", 1);
		i++;
	}
	*xx_uint = add_rgb(game, line, 0, 0);
	game->data->info_collected += 1;
}

void	add_textures(t_game *game, char *line, char **texture_xx)
{
	line = dmh(game, 0, ft_strtrim(line, " "));
	if (!line)
		clean_exit(game, "Allocation failed at trimming line.", 1);
	if (*texture_xx != NULL)
		clean_exit(game, "Same texture already defined.", 1);
	if (ft_strchr(line, ' ') != NULL || ft_strchr(line, '\t') != NULL)
		clean_exit(game, "Texture path contains spaces or tabs.", 1);
	if (ft_strlen(line) < 4 || ft_strcmp(line + (ft_strlen(line) - 4), ".xpm"))
		clean_exit(game, "Texture is not in xpm format.", 1);
	if (access(line, R_OK) == -1)
		clean_exit(game, "Texture path cannot be accessed.", 1);
	*texture_xx = dmh(game, 0, ft_strdup(line));
	if (!(*texture_xx))
		clean_exit(game, "Allocation failed at adding texture.", 1);
	game->data->info_collected += 1;
}

void	find_texture_or_color(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO", 2) && line[2] == ' ')
		add_textures(game, line + 2, &game->data->texture_no);
	else if (!ft_strncmp(line, "SO", 2) && line[2] == ' ')
		add_textures(game, line + 2, &game->data->texture_so);
	else if (!ft_strncmp(line, "WE", 2) && line[2] == ' ')
		add_textures(game, line + 2, &game->data->texture_we);
	else if (!ft_strncmp(line, "EA", 2) && line[2] == ' ')
		add_textures(game, line + 2, &game->data->texture_ea);
	else if (!ft_strncmp(line, "C", 1) && line[1] == ' ')
		add_color(game, line + 1, &game->data->ceiling_uint);
	else if (!ft_strncmp(line, "F", 1) && line[1] == ' ')
		add_color(game, line + 1, &game->data->floor_uint);
	else
		clean_exit(game, "Wrong definition of color or texture.", 1);
}

void	get_map_info(t_game *game, int fd)
{
	char	*line;

	line = NULL;
	while (game->data->info_collected != 6)
	{
		line = dmh(game, 0, get_next_line(fd));
		if (line == NULL)
			break ;
		game->data->map_start_point += 1;
		if (line[0] != '\0')
		{
			while (*line == ' ')
				line++;
			if (ft_strlen(line) > 2 && (line[1] == ' ' || line[2] == ' '))
				find_texture_or_color(game, line);
			else
				break ;
		}
	}
	if (game->data->info_collected != 6)
		clean_exit(game, "Wrong definition of color or texture.", 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:46:44 by lbroms            #+#    #+#             */
/*   Updated: 2024/03/19 15:20:57 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_door_from_map(t_game *game, int y, int x)
{
	game->data->map[y][x] = 'm';
	game->data->has_open_door = 1;
}

void	close_door_if_needed(t_game *game)
{
	if (game->data->map[game->player->p_tile_y + 1]
		[game->player->p_tile_x] == 'm'
		|| game->data->map[game->player->p_tile_y - 1]
		[game->player->p_tile_x] == 'm'
		|| game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x + 1] == 'm'
		|| game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x - 1] == 'm'
		|| game->data->map[game->player->p_tile_y + 1]
		[game->player->p_tile_x + 1] == 'm'
		|| game->data->map[game->player->p_tile_y - 1]
		[game->player->p_tile_x + 1] == 'm'
		|| game->data->map[game->player->p_tile_y + 1]
		[game->player->p_tile_x - 1] == 'm'
		|| game->data->map[game->player->p_tile_y - 1]
		[game->player->p_tile_x - 1] == 'm'
		|| game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x] == 'm')
	{
		return ;
	}
	else
	{
		close_doors_in_map(game, 0, 0);
	}
}

void	handle_door(t_game *game)
{
	if (game->data->map[game->player->p_tile_y + 1]
		[game->player->p_tile_x] == 'd')
		remove_door_from_map(game, game->player->p_tile_y + 1,
			game->player->p_tile_x);
	if (game->data->map[game->player->p_tile_y - 1]
		[game->player->p_tile_x] == 'd')
		remove_door_from_map(game, game->player->p_tile_y - 1,
			game->player->p_tile_x);
	if (game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x + 1] == 'd')
		remove_door_from_map(game, game->player->p_tile_y,
			game->player->p_tile_x + 1);
	if (game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x - 1] == 'd')
		remove_door_from_map(game, game->player->p_tile_y,
			game->player->p_tile_x - 1);
	if (game->data->map[game->player->p_tile_y + 1]
		[game->player->p_tile_x + 1] == 'd')
		remove_door_from_map(game, game->player->p_tile_y + 1,
			game->player->p_tile_x + 1);
	handle_door_checks(game);
}

int	has_door_in_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->data->map[i])
	{
		while (game->data->map[i][j])
		{
			if (game->data->map[i][j] == 'd')
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	has_door_texture(t_game *game)
{
	if (access("./textures/door.xpm", R_OK) == -1)
	{
		if (game->data->has_door)
			clean_exit(game, "Door in map, but texture not present.", 1);
		return (0);
	}
	return (1);
}

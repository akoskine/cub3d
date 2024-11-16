/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:50:39 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 14:55:37 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	adjust_steps(t_game *game)
{
	if (game->ray->ray_dir_x < 0)
	{
		game->ray->x_step = -1;
		game->ray->dist_x = (game->ray->x - game->ray->map_x)
			* game->ray->delta_x;
	}
	else
	{
		game->ray->x_step = 1;
		game->ray->dist_x = (game->ray->map_x + 1.0 - game->ray->x)
			* game->ray->delta_x;
	}
	if (game->ray->ray_dir_y < 0)
	{
		game->ray->y_step = -1;
		game->ray->dist_y = (game->ray->y - game->ray->map_y)
			* game->ray->delta_y;
	}
	else
	{
		game->ray->y_step = 1;
		game->ray->dist_y = (game->ray->map_y + 1.0 - game->ray->y)
			* game->ray->delta_y;
	}
}

void	adjust_rays(t_game *game)
{
	game->ray->current_side = 0;
	while (1)
	{
		if (game->ray->dist_x < game->ray->dist_y)
		{
			game->ray->dist_x += game->ray->delta_x;
			game->ray->map_x += game->ray->x_step;
			game->ray->current_side = 1;
		}
		else
		{
			game->ray->dist_y += game->ray->delta_y;
			game->ray->map_y += game->ray->y_step;
			game->ray->current_side = 0;
		}
		if (game->data->map[game->ray->map_y][game->ray->map_x] > '0'
			&& game->data->map[game->ray->map_y][game->ray->map_x] != 'm')
		{
			if (game->data->map[game->ray->map_y][game->ray->map_x] == 'd')
				game->ray->im_door = 1;
			break ;
		}
	}
}

void	convert_rays(t_game *game)
{
	float	wall_distance;

	if (game->ray->current_side == 0)
	{
		wall_distance = game->ray->dist_y * TILE_SIZE
			- game->ray->delta_y * TILE_SIZE;
		game->ray->wall_x = game->ray->x + (game->ray->dist_y
				- game->ray->delta_y) * game->ray->ray_dir_x;
	}
	else
	{
		wall_distance = game->ray->dist_x * TILE_SIZE
			- game->ray->delta_x * TILE_SIZE;
		game->ray->wall_x = game->ray->y + (game->ray->dist_x
				- game->ray->delta_x) * game->ray->ray_dir_y;
	}
	game->ray->wall_x -= floor(game->ray->wall_x);
	if (game->ray->current_side == 1 && game->ray->ray_dir_x < 0)
		game->ray->wall_x = 1.0 - game->ray->wall_x;
	if (game->ray->current_side == 0 && game->ray->ray_dir_y > 0)
		game->ray->wall_x = 1.0 - game->ray->wall_x;
	game->ray->wall_distance = wall_distance;
}

void	dda(t_game *game, double ray_dir)
{
	game->ray->im_door = 0;
	game->ray->x = game->player->x / TILE_SIZE;
	game->ray->y = game->player->y / TILE_SIZE;
	game->ray->ray_dir_x = cos(ray_dir);
	game->ray->ray_dir_y = sin(ray_dir);
	game->ray->map_x = game->player->x / TILE_SIZE;
	game->ray->map_y = game->player->y / TILE_SIZE;
	game->ray->delta_x = fabs(1 / game->ray->ray_dir_x);
	game->ray->delta_y = fabs(1 / game->ray->ray_dir_y);
	adjust_steps(game);
	adjust_rays(game);
	convert_rays(game);
}

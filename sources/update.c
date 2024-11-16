/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:51:03 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:30:05 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_player *player, double rot_speed)
{
	player->angle += rot_speed;
	if (player->angle > 2 * M_PI)
		player->angle = player->angle - 2 * M_PI;
	if (player->angle < 0)
		player->angle = (2 * M_PI + player->angle);
	if (player->rotate == 2 || player->rotate == -2)
		player->rotate = 0;
}

void	move_player(t_game *game, int x, int y)
{
	x = game->player->p_tile_x;
	y = game->player->p_tile_y;
	game->player->p_tile_x = (int)(game->player->x + (cos(game->player->angle)
				* MOVE_SPEED * game->player->run
				* game->player->move)) / TILE_SIZE;
	game->player->p_tile_y = (int)(game->player->y + (sin(game->player->angle)
				* MOVE_SPEED * game->player->run
				* game->player->move)) / TILE_SIZE;
	if (game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x] == '0'
		|| game->data->map[game->player->p_tile_y]
		[game->player->p_tile_x] == 'm')
	{
		game->player->x += (cos(game->player->angle)
				* MOVE_SPEED * game->player->run) * game->player->move;
		game->player->y += (sin(game->player->angle)
				* MOVE_SPEED * game->player->run) * game->player->move;
	}
	else
	{
		game->player->p_tile_x = x;
		game->player->p_tile_y = y;
	}
}

int	update(t_game *game)
{
	if (game->player->move != 0)
	{
		move_player(game, 0, 0);
		if (game->data->has_door)
			handle_door(game);
	}
	if (game->player->rotate != 0)
	{
		if (game->player->rotate < 0)
			rotate_player(game->player, ROT_SPEED);
		if (game->player->rotate > 0)
			rotate_player(game->player, -ROT_SPEED);
	}
	mlx_clear_window(game->mlx->mlx, game->mlx->window);
	floor_and_sky(game);
	ray_casting(game, 0, 60);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->mlx->image, 0, 0);
	draw_minimap(game);
	draw_hud(game);
	hud_counter(game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:54:04 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:17:48 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_image(t_game *game, size_t image, int x, int y)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->minimap->mm_images[image], x * 4 + 2, y * 4 + 2);
}

void	draw_out(t_game *game, int y)
{
	int	x;

	x = 0;
	while (x < 30)
	{
		draw_minimap_image(game, 3, x, y);
		x++;
	}
}

int	draw_x(t_game *game, int x, int y)
{
	while (x < 30 && game->minimap->x_end > x
		&& game->minimap->x_start < game->minimap->x_end)
	{
		if (game->data->map[game->minimap->y_start]
			[game->minimap->x_start] == '1')
			draw_minimap_image(game, 1, x, y);
		else
			draw_minimap_image(game, 2, x, y);
		x++;
		game->minimap->x_start++;
	}
	return (x);
}

void	draw_from_map(t_game *game, int y)
{
	int	x;

	x = 0;
	game->minimap->x_start = game->player->p_tile_x - 14;
	game->minimap->x_end = game->data->width;
	while (game->minimap->x_start < 0)
	{
		draw_minimap_image(game, 3, x, y);
		game->minimap->x_start++;
		x++;
		game->minimap->x_end++;
	}
	x = draw_x(game, x, y);
	while (x < 30)
	{
		draw_minimap_image(game, 3, x, y);
		x++;
	}
}

void	draw_minimap(t_game *game)
{
	int	y;

	y = 0;
	game->minimap->y_start = game->player->p_tile_y - 9;
	game->minimap->y_end = game->data->rows;
	while (game->minimap->y_start < 0)
	{
		draw_out(game, y);
		game->minimap->y_start++;
		game->minimap->y_end++;
		y++;
	}
	while (y < 20 && game->minimap->y_end > y
		&& game->minimap->y_start < game->minimap->y_end)
	{
		draw_from_map(game, y);
		game->minimap->y_start++;
		y++;
	}
	y -= 1;
	while (y++ < 19)
		draw_out(game, y);
	draw_minimap_image(game, 0, 14, 9);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->minimap->mm_images[4], 0, 0);
}

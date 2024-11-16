/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:51:11 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:31:19 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx->mlx, game->mlx->window);
	clean_exit(game, NULL, 0);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 14)
		game->player->run = 2;
	if (keycode == 13)
		game->player->move = 1;
	if (keycode == 1)
		game->player->move = -1;
	if (keycode == 0)
		game->player->rotate = 1;
	if (keycode == 2)
		game->player->rotate = -1;
	if (keycode == 53)
		close_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 14)
		game->player->run = 1;
	if (keycode == 13)
		game->player->move = 0;
	if (keycode == 1)
		game->player->move = 0;
	if (keycode == 0)
		game->player->rotate = 0;
	if (keycode == 2)
		game->player->rotate = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	y = 0;
	mlx_mouse_move(game->mlx->window, x, 360);
	if (game->data->mouse_flag == 0)
	{
		game->data->mouse_flag = 1;
		game->data->mouse = x;
	}
	if (x < game->data->mouse)
	{
		game->player->rotate = 2;
		x += 1;
	}
	if (x > game->data->mouse)
	{
		game->player->rotate = -2;
		x -= 1;
	}
	game->data->mouse = x;
	return (0);
}

void	start_game(t_game *game)
{
	mlx_mouse_move(game->mlx->window, 540, 360);
	mlx_mouse_hide();
	mlx_hook(game->mlx->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx->window, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx->window, 06, 1L << 6, mouse_move, game);
	mlx_hook(game->mlx->window, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx->mlx, &update, game);
	floor_and_sky(game);
	ray_casting(game, 0, 60);
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->mlx->image, 0, 0);
	draw_minimap(game);
	draw_hud(game);
	hud_counter(game);
	mlx_loop(game->mlx->mlx);
}

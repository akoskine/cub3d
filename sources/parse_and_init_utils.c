/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:49:47 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:24:26 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_minimap	*new_minimap(t_game *game)
{
	t_minimap	*ret;
	int			y;
	int			x;

	ret = dmh(game, sizeof(t_minimap), NULL);
	if (!ret)
		clean_exit(game, "Allocation of minimap failed.", 1);
	ret->mm_images = dmh(game, sizeof(void *) * 5, NULL);
	if (!ret->mm_images)
		clean_exit(game, "Allocation of minimap images failed.", 1);
	ret->mm_images[0] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/minimap_player.xpm", &x, &y);
	ret->mm_images[1] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/minimap_wall.xpm", &x, &y);
	ret->mm_images[2] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/minimap_floor.xpm", &x, &y);
	ret->mm_images[3] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/minimap_out.xpm", &x, &y);
	ret->mm_images[4] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/minimap_sides.xpm", &x, &y);
	return (ret);
}

t_window	*new_window(t_game *game)
{
	t_window	*window;

	window = (t_window *)dmh(game, sizeof(t_window), NULL);
	window->width = 1080;
	window->height = 720;
	return (window);
}

t_player	*new_player(t_file_data *data, t_game *game)
{
	t_player	*player;

	player = (t_player *)dmh(game, sizeof(t_player), NULL);
	player->x = data->player_col * TILE_SIZE;
	player->y = data->player_row * TILE_SIZE;
	data->map[(int)data->player_row][(int)data->player_col] = '0';
	if (data->faced == 'S')
		player->angle = M_PI / 2;
	else if (data->faced == 'N')
		player->angle = 3 * M_PI / 2;
	else if (data->faced == 'E')
		player->angle = 0;
	else
		player->angle = M_PI;
	player->move = 0;
	player->rotate = 0;
	player->run = 1;
	player->p_tile_x = game->data->player_col;
	player->p_tile_y = game->data->player_row;
	return (player);
}

t_ray	*new_ray(t_game *game)
{
	t_ray	*ray;

	ray = (t_ray *)dmh(game, sizeof(t_ray), NULL);
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->x = 0;
	ray->y = 0;
	ray->dist_x = 0;
	ray->dist_y = 0;
	ray->x_step = 0;
	return (ray);
}

t_mlx	*new_mlx(t_game *game)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)dmh(game, sizeof(t_mlx), NULL);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, 1080, 720, "cub3d");
	mlx->image = mlx_new_image(mlx->mlx, 1080, 720);
	mlx->addr = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	return (mlx);
}

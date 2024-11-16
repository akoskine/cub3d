/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:50:53 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 15:26:29 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_and_sky(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->window->width)
	{
		while (j < game->window->height / 2)
		{
			my_mlx_pixel_put(game->mlx, i, j, game->tex->sky_color);
			j++;
		}
		j = game->window->height / 2;
		while (j < game->window->height)
		{
			my_mlx_pixel_put(game->mlx, i, j, game->tex->ground_color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	make_3d(t_game *game, int column, float ray_angle)
{
	float	correct_angle;
	float	tex_inc;

	correct_angle = game->player->angle - ray_angle;
	if (correct_angle > 2 * M_PI)
		correct_angle = correct_angle - 2 * M_PI;
	if (correct_angle < 0)
		correct_angle = (2 * M_PI + correct_angle);
	calc_height(game, correct_angle);
	tex_inc = 1.0 * game->tex->height / game->stuff->wall_height;
	set_texture_x(game);
	smoothen_wall_textures(game, tex_inc);
	while (game->stuff->wall_start < game->stuff->wall_end)
	{
		my_mlx_pixel_put(game->mlx, column,
			game->stuff->wall_start, get_texture(tex_inc, game, ray_angle));
		game->stuff->wall_start++;
	}
	game->stuff->wall_start = 720 / 2 - game->stuff->wall_height / 2;
	game->tex->row = 0;
	game->tex->next->row = 0;
	game->tex->next->next->row = 0;
	game->tex->next->next->next->row = 0;
	if (game->data->has_door)
		game->tex->next->next->next->next->row = 0;
}

void	ray_casting(t_game *game, int i, int fov)
{
	float	current_ray_angle;
	float	fov_in_rad;
	float	dir_offset;
	float	offset_increment;

	i = 0;
	current_ray_angle = game->player->angle;
	fov = 60;
	fov_in_rad = fov * (M_PI / 180);
	dir_offset = fov_in_rad / 2 * -1;
	offset_increment = fov_in_rad / 1080;
	while (i < 1080)
	{
		current_ray_angle = game->player->angle + dir_offset;
		if (current_ray_angle > 2 * M_PI)
			current_ray_angle = (current_ray_angle - 2 * M_PI);
		if (current_ray_angle < 0)
			current_ray_angle = (2 * M_PI + current_ray_angle);
		dda(game, current_ray_angle);
		make_3d(game, i, current_ray_angle);
		i++;
		dir_offset += offset_increment;
	}
}

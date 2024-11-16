/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:50:48 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:00:53 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	calc_height(t_game *game, float correct_angle)
{
	game->stuff->wall_distance = cos(correct_angle) * game->ray->wall_distance;
	if (game->stuff->wall_distance == 0)
		game->stuff->wall_distance = 1;
	game->stuff->wall_height = 64 * 720 / game->stuff->wall_distance;
	game->stuff->wall_start = 720 / 2 - game->stuff->wall_height / 2;
	game->stuff->wall_end = 720 / 2 + game->stuff->wall_height / 2;
}

void	smoothen_wall_textures(t_game *game, float tex_inc)
{
	int	to_increment;

	if (game->stuff->wall_start >= 0)
		return ;
	to_increment = abs(game->stuff->wall_start);
	game->stuff->wall_start += to_increment;
	game->tex->row += to_increment * tex_inc;
	game->tex->next->row += to_increment * tex_inc;
	game->tex->next->next->row += to_increment * tex_inc;
	game->tex->next->next->next->row += to_increment * tex_inc;
	if (game->data->has_door)
		game->tex->next->next->next->next->row += to_increment * tex_inc;
	if (game->stuff->wall_end > 720)
		game->stuff->wall_end = 720;
}

void	set_texture_x(t_game *game)
{
	game->tex->col = (int)(game->ray->wall_x * (float)game->tex->width);
	game->tex->next->col = (int)(game->ray->wall_x
			* (float)game->tex->next->width);
	game->tex->next->next->col = (int)(game->ray->wall_x
			* (float)game->tex->next->width);
	game->tex->next->next->next->col = (int)(game->ray->wall_x
			* (float)game->tex->next->width);
	if (game->data->has_door)
	{
		game->tex->next->next->next->next->col = (int)(game->ray->wall_x
				* (float)game->tex->next->width);
	}
}

int	get_texture(float tex_inc, t_game *game, float ray_angle)
{
	int		ret;
	int		side;
	float	angle;
	t_tex	*tmp;

	tmp = game->tex;
	side = 1;
	angle = ray_angle;
	if (game->ray->im_door)
		side = 5;
	else if (game->ray->current_side == 1 && ((angle >= 0 && angle < M_PI / 2)
			|| angle > 3 * M_PI / 2))
		side = 1;
	else if (game->ray->current_side == 0 && angle > M_PI && angle < 2 * M_PI)
		side = 2;
	else if (game->ray->current_side == 0)
		side = 3;
	else
		side = 4;
	while (--side > 0)
		tmp = tmp->next;
	ret = *(int *)(tmp->addr + (4 * tmp->width
				* (int)tmp->row) + (4 * tmp->col));
	tmp->row = tmp->row + tex_inc;
	return (ret);
}

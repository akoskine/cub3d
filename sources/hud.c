/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:25:38 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:02:25 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_hud	*new_hud(t_game *game)
{
	t_hud	*ret;
	int		y;
	int		x;

	ret = dmh(game, sizeof(t_hud), NULL);
	if (!ret)
		clean_exit(game, "Allocation of hud failed.", 1);
	ret->h_images = dmh(game, sizeof(void *) * 3, NULL);
	if (!ret->h_images)
		clean_exit(game, "Allocation of hud images failed.", 1);
	ret->h_images[0] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/hud_face_1.xpm", &x, &y);
	ret->h_images[1] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/hud_face_2.xpm", &x, &y);
	ret->h_images[2] = mlx_xpm_file_to_image(game->mlx->mlx,
			"./textures/hud_face_3.xpm", &x, &y);
	ret->rate_counter = 0;
	ret->face_nbr = 0;
	return (ret);
}

void	hud_counter(t_game *game)
{
	if (game->hud->rate_counter == 30)
	{
		if (game->hud->face_nbr == 2)
			game->hud->face_nbr = 0;
		else
			game->hud->face_nbr++;
		game->hud->rate_counter = 0;
	}
	else
		game->hud->rate_counter++;
}

void	draw_hud(t_game *game)
{
	mlx_put_image_to_window(game->mlx->mlx, game->mlx->window,
		game->hud->h_images[game->hud->face_nbr], 502, 620);
}

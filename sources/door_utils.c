/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbroms <lbroms@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:57:40 by lbroms            #+#    #+#             */
/*   Updated: 2024/03/19 15:22:29 by lbroms           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_doors_in_map(t_game *game, int i, int j)
{
	while (game->data->map[i])
	{
		while (game->data->map[i][j])
		{
			if (game->data->map[i][j] == 'm')
				game->data->map[i][j] = 'd';
			j++;
		}
		j = 0;
		i++;
	}
}

void	handle_door_checks(t_game *game)
{
	if (game->data->map[game->player->p_tile_y - 1]
		[game->player->p_tile_x + 1] == 'd')
		remove_door_from_map(game, game->player->p_tile_y - 1,
			game->player->p_tile_x + 1);
	if (game->data->map[game->player->p_tile_y + 1]
		[game->player->p_tile_x - 1] == 'd')
		remove_door_from_map(game, game->player->p_tile_y + 1,
			game->player->p_tile_x - 1);
	if (game->data->map[game->player->p_tile_y - 1]
		[game->player->p_tile_x - 1] == 'd')
		remove_door_from_map(game, game->player->p_tile_y - 1,
			game->player->p_tile_x - 1);
	if (game->data->has_open_door)
		close_door_if_needed(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:50:17 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:08:54 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_walls_near_space(t_game *game, int row, int col)
{
	if (row != 0)
	{
		if (col != 0 && game->data->map[row - 1][col - 1] == '0')
			clean_exit(game, "Outer wall missing.", 1);
		if (game->data->map[row - 1][col] == '0')
			clean_exit(game, "Outer wall missing.", 1);
		if (col != (game->data->width - 1)
			&& game->data->map[row - 1][col + 1] == '0')
			clean_exit(game, "Outer wall missing.", 1);
	}
	if (col != 0 && game->data->map[row][col - 1] == '0')
		clean_exit(game, "Outer wall missing.", 1);
	if (col != (game->data->width - 1)
		&& game->data->map[row][col + 1] == '0')
		clean_exit(game, "Outer wall missing.", 1);
	if (row != (game->data->rows - 1))
	{
		if (col != 0 && game->data->map[row + 1][col - 1] == '0')
			clean_exit(game, "Outer wall missing.", 1);
		if (game->data->map[row + 1][col] == '0')
			clean_exit(game, "Outer wall missing.", 1);
		if ((col != game->data->width - 1)
			&& game->data->map[row + 1][col + 1] == '0')
			clean_exit(game, "Outer wall missing.", 1);
	}
}

void	check_doors_near_space(t_game *game, int row, int col)
{
	if (row != 0)
	{
		if (col != 0 && game->data->map[row - 1][col - 1] == 'd')
			clean_exit(game, "Outer wall missing.", 1);
		if (game->data->map[row - 1][col] == 'd')
			clean_exit(game, "Outer wall missing.", 1);
		if (col != (game->data->width - 1)
			&& game->data->map[row - 1][col + 1] == 'd')
			clean_exit(game, "Outer wall missing.", 1);
	}
	if (col != 0 && game->data->map[row][col - 1] == 'd')
		clean_exit(game, "Outer wall missing.", 1);
	if (col != (game->data->width - 1)
		&& game->data->map[row][col + 1] == 'd')
		clean_exit(game, "Outer wall missing.", 1);
	if (row != (game->data->rows - 1))
	{
		if (col != 0 && game->data->map[row + 1][col - 1] == 'd')
			clean_exit(game, "Outer wall missing.", 1);
		if (game->data->map[row + 1][col] == 'd')
			clean_exit(game, "Outer wall missing.", 1);
		if ((col != game->data->width - 1)
			&& game->data->map[row + 1][col + 1] == 'd')
			clean_exit(game, "Outer wall missing.", 1);
	}
}

void	check_walls(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < game->data->rows)
	{
		col = 0;
		while (col < game->data->width)
		{
			if (game->data->map[row][col] == ' ')
			{
				check_walls_near_space(game, row, col);
				check_doors_near_space(game, row, col);
			}
			if ((game->data->map[row][col] == '0'
				|| game->data->map[row][col] == 'd') && (col == 0 ||
				col == (game->data->width - 1) || row == 0
				|| row == (game->data->rows - 1)))
				clean_exit(game, "Outer wall missing.", 1);
			col++;
		}
		row++;
	}
}

void	check_player(t_game *game, int row, int col, char c)
{
	while (game->data->map[++row])
	{
		col = -1;
		while (game->data->map[row][++col])
		{
			c = game->data->map[row][col];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (game->data->player_row != -1)
					clean_exit(game, "Multiple players in map.", 1);
				game->data->player_row = row;
				game->data->player_col = col;
				game->data->faced = game->data->map[row][col];
			}
			else if (c != '0' && c != '1' && c != ' ' && c != 'd')
				clean_exit(game, "Invalid character in map.", 1);
		}
	}
	if (row < 3 || game->data->player_row == -1)
		clean_exit(game, "Player missing or incomplete map.", 1);
	if (game->data->player_row == 0
		|| game->data->player_row == (game->data->rows - 1)
		|| game->data->player_col == 0
		|| game->data->player_col == (game->data->width - 1))
		clean_exit(game, "Player is located in outerwall.", 1);
}

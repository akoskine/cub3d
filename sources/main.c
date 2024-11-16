/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:49:19 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:08:31 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	parse_and_init(game, argc, argv);
	start_game(game);
	return (0);
}

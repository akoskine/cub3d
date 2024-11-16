/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:50:25 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:23:19 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->player = NULL;
	game->ray = NULL;
	game->window = NULL;
	game->tex = NULL;
	game->stuff = NULL;
	game->data = NULL;
	game->minimap = NULL;
	game->dmh_list = NULL;
}

void	init_file_data(t_game *game)
{
	game->data->map = NULL;
	game->data->player_row = -1;
	game->data->player_col = -1;
	game->data->map_start_point = 0;
	game->data->rows = 0;
	game->data->width = 0;
	game->data->faced = '\0';
	game->data->info_collected = 0;
	game->data->texture_no = NULL;
	game->data->texture_so = NULL;
	game->data->texture_we = NULL;
	game->data->texture_ea = NULL;
	game->data->floor_uint = 0;
	game->data->ceiling_uint = 0;
	game->data->mouse = 0;
	game->data->mouse_flag = 0;
}

t_tex	*load_textures(t_game *game, char *path)
{
	t_tex	*ret;
	int		width;
	int		height;

	width = 64;
	height = 64;
	ret = dmh(game, sizeof(t_tex), NULL);
	ret->tex = mlx_xpm_file_to_image(game->mlx->mlx, path, &width, &height);
	ret->addr = mlx_get_data_addr(ret->tex, &ret->bpp, &ret->width,
			&ret->endian);
	ret->col = 0;
	ret->row = 0;
	ret->width = width;
	ret->height = height;
	ret->sky_color = game->data->ceiling_uint;
	ret->ground_color = game->data->floor_uint;
	ret->next = NULL;
	return (ret);
}

void	init_structs(t_game *game)
{
	game->mlx = new_mlx(game);
	game->player = new_player(game->data, game);
	game->ray = new_ray(game);
	game->window = new_window(game);
	game->minimap = new_minimap(game);
	game->hud = new_hud(game);
	game->stuff = dmh(game, sizeof(t_threedstuff), NULL);
	game->stuff->wall_distance = 0;
	game->stuff->wall_height = 0;
	game->stuff->wall_end = 0;
	game->stuff->wall_start = 0;
	game->tex = load_textures(game, game->data->texture_ea);
	game->tex->next = load_textures(game, game->data->texture_no);
	game->tex->next->next = load_textures(game, game->data->texture_so);
	game->tex->next->next->next = load_textures(game, game->data->texture_we);
	game->data->has_door = has_door_in_map(game);
	game->data->has_open_door = 0;
	if (game->data->has_door)
		game->tex->next->next->next->next
			= load_textures(game, "./textures/door.xpm");
}

void	parse_and_init(t_game *game, int argc, char **argv)
{
	int	fd;
	int	fd2;

	if (argc != 2)
		clean_exit(game, "Wrong arguments! Syntax: ./cub3d <mapfile>.", 1);
	if (!ft_strchr(argv[1], '.')
		|| ft_strcmp(ft_strchr(argv[1], '.'), ".cub") != 0)
		clean_exit(game, "Wrong file format! Use .cub format instead.", 1);
	init_game(game);
	game->data = (t_file_data *)dmh(game, sizeof(t_file_data), NULL);
	if (!game->data)
		clean_exit(game, "game->data (t_file_data *) allocation failed.", 1);
	init_file_data(game);
	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[1], O_RDONLY);
	if (fd < 0 || fd2 < 0)
		clean_exit(game, "Failed to open file.", 1);
	get_map_info(game, fd);
	get_map_size(game, fd);
	create_2d_map(game, fd2);
	check_player(game, -1, -1, 'c');
	check_walls(game);
	close(fd);
	close(fd2);
	init_structs(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:49:34 by akoskine          #+#    #+#             */
/*   Updated: 2024/03/19 19:34:05 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define TILE_SIZE 64
# define ROT_SPEED 0.1
# define MOVE_SPEED 3.0		

typedef struct s_dmh
{
	void			*void_hold;
	struct s_dmh	*next;
}	t_dmh;

typedef struct s_mlx
{
	void			*mlx;
	void			*image;
	void			*window;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}			t_mlx;

typedef struct s_hud
{
	void			**h_images;
	int				rate_counter;
	int				face_nbr;
}			t_hud;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			angle;
	int				move;
	int				rotate;
	int				run;
	int				p_tile_x;
	int				p_tile_y;
}			t_player;

typedef struct s_ray
{
	int				im_door;
	double			x;
	double			y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_x;
	double			delta_y;
	int				x_step;
	int				y_step;
	double			dist_x;
	double			dist_y;
	int				current_side;
	int				wall_distance;
	float			wall_x;
}			t_ray;

typedef struct s_window
{
	int				width;
	int				height;
}			t_window;

typedef struct s_threedstuff
{
	int				wall_height;
	int				wall_start;
	int				wall_end;
	int				wall_distance;
}			t_threedstuff;

typedef struct s_tex
{
	void			*tex;
	void			*addr;
	int				bpp;
	int				endian;
	int				col;
	float			row;
	int				width;
	int				height;
	int				sky_color;
	int				ground_color;
	struct s_tex	*next;
}			t_tex;

typedef struct s_minimap
{
	void			**mm_images;
	int				x_start;
	int				x_end;
	int				y_start;
	int				y_end;
}			t_minimap;

typedef struct s_file_data
{
	int				has_door;
	int				has_open_door;
	char			**map;
	double			player_row;
	double			player_col;
	int				map_start_point;
	int				rows;
	int				width;
	char			faced;
	int				info_collected;
	char			*texture_no;
	char			*texture_so;
	char			*texture_we;
	char			*texture_ea;
	int				floor_uint;
	int				ceiling_uint;
	int				mouse;
	int				mouse_flag;
}			t_file_data;

typedef struct s_game
{
	t_mlx			*mlx;
	t_player		*player;
	t_ray			*ray;
	t_window		*window;
	t_tex			*tex;
	t_threedstuff	*stuff;
	t_file_data		*data;
	t_minimap		*minimap;
	t_dmh			*dmh_list;
	t_hud			*hud;
}				t_game;

/* main.c */
int				main(int argc, char **argv);

/* parse_and_init.c */
void			init_game(t_game *game);
void			init_file_data(t_game *game);
t_tex			*load_textures(t_game *game, char *path);
void			init_structs(t_game *game);
void			parse_and_init(t_game *game, int argc, char **argv);

/* parse_and_init_utils.c */
t_minimap		*new_minimap(t_game *game);
t_window		*new_window(t_game *game);
t_player		*new_player(t_file_data *data, t_game *game);
t_ray			*new_ray(t_game *game);
t_mlx			*new_mlx(t_game *game);

/* utils.c */
int				close_game(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				mouse_move(int x, int y, t_game *game);
void			start_game(t_game *game);

/* map_information.c */
int				add_rgb(t_game *game, char *line, int count, int idx);
void			add_color(t_game *game, char *line, int *xx_uint);
void			add_textures(t_game *game, char *line, char **texture_xx);
void			find_texture_or_color(t_game *game, char *line);
void			get_map_info(t_game *game, int fd);

/* create_map.c */
void			add_rows_2d_map(t_game *game, int fd2);
void			create_2d_map(t_game *game, int fd2);
void			get_map_size(t_game *game, int fd);

/* map_validation.c */
void			check_doors_near_space(t_game *game, int row, int col);
void			check_walls_near_space(t_game *game, int row, int col);
void			check_walls(t_game *game);
void			check_player(t_game *game, int row, int col, char c);

/* draw.c */
void			floor_and_sky(t_game *game);
void			make_3d(t_game *game, int column, float ray_angle);
void			ray_casting(t_game *game, int i, int fov);

/* draw_utils.c */
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void			calc_height(t_game *game, float correct_angle);
void			smoothen_wall_textures(t_game *game, float tex_inc);
void			set_texture_x(t_game *game);
int				get_texture(float tex_inc, t_game *game, float ray_angle);

/* dda.c */
void			adjust_steps(t_game *game);
void			adjust_rays(t_game *game);
void			convert_rays(t_game *game);
void			dda(t_game *game, double ray_dir);

/* minimap.c */
void			draw_minimap_image(t_game *game, size_t image, int x, int y);
void			draw_out(t_game *game, int y);
int				draw_x(t_game *game, int x, int y);
void			draw_from_map(t_game *game, int y);
void			draw_minimap(t_game *game);

/* door.c */
void			remove_door_from_map(t_game *game, int y, int x);
void			close_door_if_needed(t_game *game);
void			handle_door(t_game *game);
int				has_door_in_map(t_game *game);
int				has_door_texture(t_game *game);
void			handle_door_checks(t_game *game);
void			close_doors_in_map(t_game *game, int i, int j);

/* hud.c */
t_hud			*new_hud(t_game *game);
void			hud_counter(t_game *game);
void			draw_hud(t_game *game);

/* update.c */
void			rotate_player(t_player *player, double rot_speed);
void			move_player(t_game *game, int x, int y);
int				update(t_game *game);

/*dmh*/
void			*dmh(t_game *game, size_t size, void *ptr);
t_dmh			*dmh_new(size_t size, void *ptr);
void			free_dmh(t_game *game);
void			clean_exit(t_game *game, char *msg, int exit_code);

#endif

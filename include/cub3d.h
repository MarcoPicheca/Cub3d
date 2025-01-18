/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:21:13 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/18 17:41:44 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include "./colors.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define V 118
# define M 109
# define PI 3.141592653
# define BLOCK 81
# define LEFT 65361
# define RIGHT 65363

typedef struct s_ray_result
{
	float	hit_x;
	float	hit_y;
	int		side;
}			t_ray_result;

typedef struct s_ray_cast_params
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side_local;
	float	perp_wall_dist;
	float	hit_x;
	float	hit_y;
}			t_ray_cast_params;

typedef struct s_rectangle_params
{
	float	start_x;
	float	start_y;
	float	width;
	float	height;
	int		color;
}			t_rectangle_params;

typedef struct s_render_3d_settings
{
	float	fov;
	float	angle_step;
	int		center_ray;
	int		num_rays;
}			t_render_3d_settings;

typedef struct s_3d_properties
{
	float	ray_angle;
	float	ray_dir_x;
	float	ray_dir_y;
	float	hit_x;
	float	hit_y;
	int		side_local;
}			t_3d_properties;

typedef struct s_crosshair_params
{
	int		size;
	int		dy;
	int		dx;
	int		px;
	int		py;
}			t_crosshair_params;

typedef struct s_tex
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_size;
	int		endian;
}			t_tex;

typedef struct s_draw_data
{
	float	dist;
	float	correct_dist;
	float	wall_height_f;
	int		wall_height;
	int		wall_top;
	int		wall_bot;
	t_tex	*used_tex;
	int		tex_x;
	float	step;
}			t_draw_data;

typedef struct s_ray
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	float	step_size;
	float	distance;
}			t_ray;

typedef struct s_rays_2d
{
	float	angle_step;
	float	start_angle;
	float	ray_angle;
	float	hit_x;
	float	hit_y;
	float	distance;
	float	end_x;
	float	end_y;
	float	start_x;
	float	start_y;
	float	stepx;
	float	stepy;
	float	cx;
	float	cy;
}			t_rays_2d;

typedef struct s_game	t_game;

typedef struct s_play
{
	char	dir_start;
	t_game	*game;
	double	pos_x;
	double	pos_y;
	int		found;
	float	x;
	float	y;
	float	angle;
	float	angle_speed;
	float	move_speed;
	float	rot_speed;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		left_rotate;
	int		right_rotate;
	void	*hands;
	int		render_mode;
	int		minimap_view;
}			t_play;

typedef struct s_render_2d
{
	float	scale_x;
	float	scale_y;
	float	fov;
	int		square_size;
	int		player_size;
	int		color_wall2d;
	int		color_player;
	int		color_ray;
	int		color_wall;
	int		num_rays;
}			t_render_2d;

typedef struct s_crdls
{
	char	*path_s;
	char	*path_n;
	char	*path_w;
	char	*path_e;
}			t_crdls;

typedef struct s_txt
{
	int		fl_r;
	int		fl_g;
	int		fl_b;
	int		cl_r;
	int		cl_g;
	int		cl_b;
	char	*path_txt_floor;
	char	*path_txt_ceiling;
}			t_txt;

typedef struct s_mini
{
	int		minimap_size;
	int		cell_size;
	int		offset_x;
	int		offset_y;
	int		x;
	int		y;
	int		minimap_x;
	int		minimap_y;
	int		minimap_colors;
}			t_mini;

typedef struct s_map
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	*pathxpm;
	char	**mtx2;
	char	*path_hands;
	int		ceiling_color;
	int		floor_color;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
	int		lines_ind;
	int		cols_ind;
	int		len_map;
	int		start_map;
	int		end_map;
	int		ht;
	int		wh;
	int		x;
	int		y;
	int		fd;
	int		main_chr;
	char	**mtx;
	t_crdls	cardinals;
	t_txt	txt;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*img;
	void	*win;
	char	*img_data;
	int		bpp;
	int		line_size;
	int		endian;
	t_tex	tex_hands;
	t_tex	tex_no;
	t_tex	tex_so;
	t_tex	tex_we;
	t_tex	tex_ea;
	t_play	player;
	t_map	map;
	t_tex	my_tex;
	t_mini	minimap;
}			t_game;

// parsing
void	free_txt(t_txt *txt);
int		ft_is_cub(char *str, int len, char *ext);
int		file_cub_check(char *str);
int		map_gen(t_game *game, char *av);
void	free_matrix(char **map, int len);
void	free_game(t_game *game);
void	free_crlds(t_map *map);
char	*get_next_line(int fd);
int		map_div(t_map *map, t_game *game);
int		map_game(t_map *map, t_game *game);
int		map_cardinal(t_map *map);
int		map_texture_f_c(t_map *map);
int		err_game_card(t_map *map);
void	map_isnt_close(int x, int y, char **tmp, int len);
void	move_to_first_char(char **tmp, t_map *map);
int		check_flood(char **tmp, int len);
int		flood_phil(t_map *map, char **tmp);
int		check_map_tmp(t_map *map);
int		check_rgb_txt(t_txt *txt);
int		file_path(char *str);

// movment
void	set_angles_on_rotation(t_play *player);
void	update_position(t_play *player, t_map *map, float move_x, float move_y);
void	move_player(t_play *player, t_map *map);

// drawing functions
void	draw_ray_dda(t_game *game, float angle, int color);
void	draw_player(t_game *game, t_render_2d *params);
void	draw_rays(t_game *game, t_render_2d *params);

// rendering
bool	touch(float px, float py, t_game *game);
void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
void	init_render_2d(t_render_2d *params, t_game *game);
void	render_map(t_game *game);
void	init_render_3d_view(t_render_3d_settings *settings);

// game init
int		game_loop(t_game *game);
void	init_game(t_game *game);

// utils game
int		key_press(int keycode, t_play *player);
int		key_release(int keycode, t_play *player);
int		close_window(t_game *game);
char	**copy_map_in_mtx2(t_map *map);
int		init_map(t_map *map, t_play *player);
void	free_matrix2(char **map);
void	count_map_dimensions(t_map *map);

void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);
bool	touch(float px, float py, t_game *game);
void	normalize_angle(float *angle);

void	render_map(t_game *game);
void	init_game(t_game *game);
void	draw_rectangle(t_rectangle_params *params, t_game *game);

int		ft_is_cub(char *str, int len, char *ext);
int		file_cub_check(char *str);
int		map_gen(t_game *game, char *av);
char	*get_next_line(int fd);

void	load_textures(t_game *game);
float	cast_ray_dda_side(t_game *game, float angle, t_ray_result *result);
void	render_3d_view(t_game *game);
void	draw_hands(t_game *game);

void	draw_map(t_game *game, t_render_2d *values);
void	draw_player(t_game *game, t_render_2d *values);
void	draw_rays(t_game *game, t_render_2d *values);

void	init_rays_2d(t_rays_2d *rays, t_game *game,
			t_render_2d *values, int ray_index);

void	draw_wall_column(t_game *game, t_draw_data *dd, int screen_x);
void	draw_floor_and_ceiling(t_game *game);
void	draw_single_3d_ray(t_game *game, int screen_col,
			float ray_angle, t_render_3d_settings *settings);

int		get_tex_color(t_tex *tex, int tx, int ty);

t_tex	*pick_texture(t_game *game, t_3d_properties *prop);
int		compute_tex_x(t_tex *used_tex, t_3d_properties *prop);
void	init_render_3d_prop(t_3d_properties *prop, float angle);
void	init_params_for_draw_single_3d_ray(t_draw_data *dd,
			t_3d_properties *prop, t_game *game);
float	cast_ray_dda_side(t_game *game, float angle, t_ray_result *result);

#endif
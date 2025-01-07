/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:21:13 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/07 15:03:08 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include "./colors.h"
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

// WIN DIMENSION
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

// MOVEMENTS KEYS
# define W 119
# define A 97
# define S 115
# define D 100

// Pi costant
# define PI 3.141592653
# define BLOCK 80

# define LEFT 65361
# define RIGHT 65363


typedef struct s_play
{
	char	dir_start;
	double	pos_x;
	double	pos_y;
	int		found;
    float   x;
    float   y; 
    float   angle;
	float	angle_speed;
    float   move_speed;
    float   rot_speed;
	int     key_up;
    int     key_down;
    int     key_left;
    int     key_right;
	int     left_rotate;
    int     right_rotate;
	void	*hands;
} t_play;

typedef struct s_render_2d
{
    int square_size;
    int player_size;
    int color_wall;
    int color_player;
    int color_ray;
    float fov;
    int num_rays;
} t_render_2d;

typedef struct s_crdls
{
	// mlx hands image
	void	*wall_NO;
	void	*wall_SO;
	void	*wall_EA;
	void	*wall_WS;
	char	*path_SO;
	char	*path_NO;
	char	*path_WS;
	char	*path_EA;
}			t_crdls;

typedef struct s_txt
{
	// mlx hands image
	void	*floor;
	void	*ceiling;
	int		fl_r;
	int		fl_g;
	int		fl_b;
	int		cl_r;
	int		cl_g;
	int		cl_b;
	char	*path_txt_floor;
	char	*path_txt_ceiling;
}			t_txt;

typedef struct s_map
{
	char	**mtx2;
    int		width; 
    int		height;
    int		player_x; 
    int		player_y;  
    char	player_dir; 
	int		lines_ind; //da settare quando abbiamo la matrice della mappa effettiva
	int		cols_ind; //da settare quando abbiamo la matrice della mappa effettiva
	int		len_map; //da settare quando abbiamo la matrice della mappa effettiva
	int		start_map; //da settare quando andiamo a cercare la mappa nel file
	int		end_map; //da settare quando andiamo a cercare la mappa nel file
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
	char    *img_data;      // Puntatore ai dati dell'immagine
    int     bpp;            // Bytes per pixel
    int     line_size;      // Dimensione di una riga in byte
    int     endian;         // Endianness (0: little-endian, 1: big-endian)
	void	*sky;
	t_play	player;
	t_map	map;
}			t_game;

// parsing
int		ft_is_cub(char *str, int len, char *ext);
int		file_cub_check(char *str);
int		map_gen(t_game *game, char *av);
void	free_matrix(char **map, int len);
void	free_game(t_game *game);
char	*get_next_line(int fd);
int		map_div(t_map *map, t_game *game);
int		map_game(t_map *map,  t_game *game);
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

void	put_pixel(int x, int y, int color, t_game *game);
void	draw_ray_dda(t_game *game, float angle, int color);
void	draw_square(int x, int y, int size, int color, t_game *game);

int		game_loop(t_game *game);
int		key_press(int keycode, t_play *player);
int		key_release(int keycode, t_play *player);
int		close_window(t_game *game);

void	put_pixel(int x, int y, int color, t_game *game);
void	clear_image(t_game *game);

void	move_player(t_play *player, t_map *map);

void	render_map(t_game *game);
void	init_game(t_game *game);
void	init_map(t_map *map, t_play *player);

int		ft_is_cub(char *str, int len, char *ext);
int		file_cub_check(char *str);
int		map_gen(t_game *game, char *av);
void	free_matrix(char **map);
void	free_game(t_game *game);
char	*get_next_line(int fd);

#endif
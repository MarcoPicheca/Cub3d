/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:21:13 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/16 16:58:44 by mapichec         ###   ########.fr       */
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

// typedef struct s_player
// {
// 	char	dir_start;
// 	float	x;
// 	float	y;
// }			t_player;

typedef struct s_crdls
{
	char	*path_SO;
	char	*path_NO;
	char	*path_WS;
	char	*path_EA;
}			t_crdls;

typedef struct s_txt
{
	char	*path_txt_floor;
	char	*path_txt_ceiling;
}			t_txt;

typedef struct s_map
{
	int		lines_ind; //da settare quando abbiamo la matrice della mappa effettiva
	int		cols_ind; //da settare quando abbiamo la matrice della mappa effettiva
	int		start_map; //da settare quando andiamo a cercare la mappa nel file
	int		end_map; //da settare quando andiamo a cercare la mappa nel file
	int		ht;
	int		wh;
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
	t_map	map;
}			t_game;

int		ft_is_cub(char *str, int len, char *ext);
int		file_cub_check(char *str);
int		map_gen(t_game *game, char *av);
void	free_matrix(char **map);
void	free_game(t_game *game);
char	*get_next_line(int fd);

#endif
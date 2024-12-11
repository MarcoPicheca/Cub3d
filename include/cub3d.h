/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:21:13 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/10 17:47:01 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <fcntl.h>
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

typedef struct s_player
{
	char	dir_start;
	float	x;
	float	y;
}			t_player;

typedef struct s_game
{
	void	*mlx;
	void	*img;
	void	*win;
	char	**map;
}			t_game;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4_minilibx.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:00:58 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/16 09:57:56 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
calcola l'indice/coordinata del pixel, con offset verticale e orizzontale
(per il buffer dell'immagine img_data gestito da mlx_get_data_addr)
estrazione BGR
*/
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	index = y * game->line_size + x * (game->bpp / 8);
	game->img_data[index] = color & 0xFF;
	game->img_data[index + 1] = (color >> 8) & 0xFF;
	game->img_data[index + 2] = (color >> 16) & 0xFF;
}

/*
pulisce l'intero buffer d'immagine ad ogni iterazione del loop della minilibx
*/
void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

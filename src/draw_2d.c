/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:40:03 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/15 20:43:34 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
disegna raggio per raggio (a partire da sinistra), ognuno fino al raggiungimento
della distanza aggiorna via via i coefficienti di avanzamento per colorare
i pixel che lo rappresentano
*/
void	draw_rays(t_game *game, t_render_2d *values)
{
	t_rays_2d	rays;
	int			i;
	int			j;
	int			m;
	int			n;

	i = 0;
	while (i < values->num_rays)
	{
		init_rays_2d(&rays, game, values, i);
		j = 0;
		while (j < (int)rays.distance)
		{
			m = (int)rays.cx;
			n = (int)rays.cy;
			put_pixel(m, n, values->color_ray, game);
			rays.cx += rays.stepx;
			rays.cy += rays.stepy;
			j++;
		}
		i++;
	}
}

/*
disegna il giocatore in mod 2d
usa cooridnate relative e assolute (x e y , start_x e start_y)
*/

// TODO conditional jump di params->height
void	draw_rectangle(t_rectangle_params *params, t_game *game)
{
	int	y;
	int	x;
	int	rect_x;
	int	rect_y;

	y = 0;
	while (y < (int)params->height)
	{
		x = 0;
		while (x < (int)params->width)
		{
			rect_x = (int)(params->start_x + x);
			rect_y = (int)(params->start_y + y);
			put_pixel(rect_x, rect_y, params->color, game);
			x++;
		}
		y++;
	}
}

/*
x e y sono le coordinate del centro del giocatore,
ottenute moltiplicando per il fattore di scala,
start_x e start_y sono le coordinate del primo pixel del rettangolo.
*/
void	draw_player(t_game *game, t_render_2d *values)
{
	t_rectangle_params			rect_params;
	float						x;
	float						y;
	float						half;

	x = game->player.x * values->scale_x;
	y = game->player.y * values->scale_y;
	half = values->player_size * 0.5f;
	rect_params.start_x = x - half;
	rect_params.start_y = y - half;
	rect_params.width = values->player_size;
	rect_params.height = values->player_size;
	rect_params.color = 0xFFFF00;
	draw_rectangle(&rect_params, game);
}

/*
disegna la mappa, i rettangoli.
draw_rectangle e' una f condivisa, in questo caso disegna i muri (in mod 2d)
start_x e start_y coordinate d'inizio per rendering del rettangolo
(moltiplico per loro fattore di scala) width e height grandezza del rettangolo
*/
void	draw_map(t_game *game, t_render_2d *values)
{
	t_rectangle_params	params;
	int					y;
	int					x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < ft_strlen(game->map.mtx2[y]))
		{
			if (game->map.mtx2[y][x] == '1')
			{
				params.start_x = x * values->scale_x;
				params.start_y = y * values->scale_y;
				params.width = values->scale_x;
				params.height = values->scale_y;
				params.color = values->color_wall2d;
				draw_rectangle(&params, game);
			}
			x++;
		}
		y++;
	}
}

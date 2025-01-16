/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_hands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:22:52 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/14 11:32:29 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	draw_hands(t_game *game)
{
	int	x;
	int	y;
	int	h;
	int	w;
	int	color;

	x = (WIN_WIDTH / 2) - (game->tex_hands.width / 2);
	y = WIN_HEIGHT - game->tex_hands.height - 24;
	h = 0;
	while (h < game->tex_hands.height)
	{
		w = 0;
		while (w < game->tex_hands.width)
		{
			color = get_tex_color(&game->tex_hands, w, h);
			if (color)
				put_pixel(x + w, y + h, get_tex_color(&game->tex_hands,
						w, h), game);
			w++;
		}
		h++;
	}
}

/*
inizializza i valori per il mirino
size e' la grandezze del lato
py e' il punto centrale lungo l'asse y [come win_height / 2]
x_screen e' la colonna centrale, gli diamo - 7 per avere un po
di offset per il disegno del mirino [*nota]
*/
void	init_draw_crosshair_params(t_crosshair_params *params,
			int x_screen, int wall_top, int wall_bot)
{
	params->size = 12;
	params->py = (wall_top + wall_bot) / 2;
	params->px = x_screen - 7;
}

/*
disegna il mirino
nel secondo while spostiamo le coordinate dal centro dell'area verso
il punto in alto a sinistra
*/
void	draw_crosshair(t_game *game, t_crosshair_params *params)
{
	int	dy;
	int	dx;
	int	x;
	int	y;

	dy = 0;
	while (dy < params->size)
	{
		dx = 0;
		while (dx < params->size)
		{
			x = params->px - (params->size / 2) + dx;
			y = params->py - (params->size / 2) + dy;
			if (dy == 0 || dy == params->size -1 || dx == 0
				|| dx == params->size -1)
				put_pixel(x, y, 0x00FF00, game);
			dx++;
		}
		dy++;
	}
}

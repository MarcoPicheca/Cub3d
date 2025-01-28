/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair_hands_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 08:22:52 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/24 16:59:56 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*
funzione per disegnare le mani del giocatore.
x e y calcolano l'offset orizzontale e verticale del giocare [lo centrano]
h e w sono altezza e larghezza della texture da disegnare, quindi le coordinate
in pixel. put_pixel viene chiamata solo per i pixel non 0 [ovvero 0x000000]
e' un workaround per non disegnare lo sfondo nero della texture
*/
// void	draw_hands(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	h;
// 	int	w;
// 	int	color;

// 	x = (WIN_WIDTH / 2) - (game->tex_hands.width / 2);
// 	y = WIN_HEIGHT - game->tex_hands.height - 24;
// 	h = 0;
// 	while (h < game->tex_hands.height)
// 	{
// 		w = 0;
// 		while (w < game->tex_hands.width)
// 		{
// 			color = get_tex_color(&game->tex_hands, w, h);
// 			if (color)
// 				put_pixel(x + w, y + h, get_tex_color(&game->tex_hands,
// 						w, h), game);
// 			w++;
// 		}
// 		h++;
// 	}
// }

void	update_gun_animation(t_game *game)
{
	static clock_t	last_time;
	clock_t			current_time;
	double			elapsed_time;

	current_time = clock();
	elapsed_time = (double)(current_time - last_time) / CLOCKS_PER_SEC;
	if (game->player.is_shooting && elapsed_time > 0.2)
	{
		game->player.gun_current_frame++;
		if (game->player.gun_current_frame >= 5)
		{
			game->player.gun_current_frame = 0;
			game->player.is_shooting = 0;
		}
		last_time = current_time;
	}
}

void	draw_gun(t_game *game)
{
	t_tex			*current_frame;
	t_gun_frames	values;

	current_frame = &game->player.gun_frames[0];
	if (game->player.is_shooting)
		current_frame = &game->player.gun_frames[
			game->player.gun_current_frame];
	values.x = (WIN_WIDTH / 2) - (current_frame->width / 2);
	values.y = WIN_HEIGHT - current_frame->height - 24;
	values.h = 0;
	while (values.h < current_frame->height)
	{
		values.w = 0;
		while (values.w < current_frame->width)
		{
			values.color = get_tex_color(current_frame, values.w, values.h);
			if (values.color)
				put_pixel(values.x + values.w, values.y + values.h,
					values.color, game);
			values.w++;
		}
		values.h++;
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

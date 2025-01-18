/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:45:51 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/18 17:37:07 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/cub3d_bonus.h"

/*
disegna soffitto e pavimento.
per il soffito parte da (0, 0) e arriva fino a meta dell'altezza
per il pavimento parte da meta altezza (0, height/2) e arriva fino in fondo
*/
void	draw_floor_and_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT * 0.5f)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			put_pixel(x, y,
				game->map.ceiling_color, game);
		}
		y++;
	}
	y = WIN_HEIGHT * 0.5f;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(x, y, game->map.floor_color, game);
			x++;
		}
		y++;
	}
}

/*
disegna il muro una colonna alla volta, dall'alto verso il basso [y++],
calcola la componente verticale della texture da mappare sul muro,
estrae il colore, scrive il pixel sullo schermo.
diff serve per capire dove prendere il colore della texture "scorrendola"
verticalmente [scostamento/differenza verticale]
dd->step e' un fattore di scala (quanto avanzare sulla texture in base
 ad altezza muro sullo schermo)
*/
void	draw_wall_column(t_game *game, t_draw_data *dd, int screen_x)
{
	int	y;
	int	diff;
	int	tex_y;
	int	color;

	y = dd->wall_top;
	while (y < dd->wall_bot)
	{
		if (y >= 0 && y < WIN_HEIGHT)
		{
			diff = y - dd->wall_top;
			tex_y = (int)(diff * dd->step);
			color = get_tex_color(dd->used_tex, dd->tex_x, tex_y);
			put_pixel(screen_x, y, color, game);
		}
		y++;
	}
}

#ifdef BONUS

/*
viene chiamata per ogni singolo raggio in render_3d_view, inizializza
il necessario, disegna una colonna per volta.
se la colonna e' quella centrale chiama le funzioni per disegnare il mirino.
*/
void	draw_single_3d_ray(t_game *game, int screen_col, float ray_angle,
				t_render_3d_settings *settings)
{
	t_3d_properties		prop;
	t_draw_data			dd;
	t_crosshair_params	params;

	init_render_3d_prop(&prop, ray_angle);
	init_params_for_draw_single_3d_ray(&dd, &prop, game);
	draw_wall_column(game, &dd, screen_col);
	if (screen_col == settings->center_ray)
	{
		init_draw_crosshair_params(&params, screen_col,
			dd.wall_top, dd.wall_bot);
		draw_crosshair(game, &params);
	}
}

#endif

#ifndef BONUS

/*
viene chiamata per ogni singolo raggio in render_3d_view,
inizializza il necessario, disegna una colonna per volta.
se la colonna e' quella centrale chiama le funzioni
per disegnare il mirino.
*/
void	draw_single_3d_ray(t_game *game, int screen_col, float ray_angle,
			t_render_3d_settings *settings)
{
	t_3d_properties	prop;
	t_draw_data		dd;

	(void)settings;
	init_render_3d_prop(&prop, ray_angle);
	init_params_for_draw_single_3d_ray(&dd, &prop, game);
	draw_wall_column(game, &dd, screen_col);
}

#endif

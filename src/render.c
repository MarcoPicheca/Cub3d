/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:20:15 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/24 16:22:35 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/cub3d_bonus.h"

#ifndef BONUS

/*
con il tasto 'v' cambiamo modalita'
viene chiamata da game_loop che sta in mlx_loop_hook
*/
void	render_map(t_game *game)
{
	t_render_2d	values;

	if (game->player.render_mode == 0)
	{
		init_render_2d(&values, game);
		clear_image(game);
		draw_map(game, &values);
		draw_player(game, &values);
		draw_rays(game, &values);
	}
	else
		render_3d_view(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/*
funzione per la resa 3d
l'angolo iniziale e' quello a sinistra[il centrale(player.angle) - la meta
del field of view]per ogni raggio abbiamo un angolo diverso e una chiamata
per disegnare una colonna alla volta da sinistra a destra.
angle_step e' la differenza in radianti tra ogni raggio
*/
void	render_3d_view(t_game *game)
{
	t_render_3d_settings	settings;
	int						r;
	float					start_angle;
	float					current_angle;

	draw_floor_and_ceiling(game);
	init_render_3d_view(&settings);
	start_angle = game->player.angle - (settings.fov / 2.0f);
	r = 0;
	while (r < settings.num_rays)
	{
		current_angle = start_angle + r * settings.angle_step;
		draw_single_3d_ray(game, r, current_angle, &settings);
		r++;
	}
}

#endif

#ifdef BONUS

/*
con il tasto 'v' cambiamo modalita'
viene chiamata da game_loop che sta in mlx_loop_hook
*/
void	render_map(t_game *game)
{
	t_render_2d	values;

	if (game->player.render_mode == 0)
	{
		init_render_2d(&values, game);
		clear_image(game);
		draw_map(game, &values);
		draw_player(game, &values);
		draw_rays(game, &values);
	}
	else
	{
		render_3d_view(game);
		if (game->player.minimap_view == 0)
			draw_minimap(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/*
funzione per la resa 3d
l'angolo iniziale e' quello a sinistra[il centrale(player.angle) - la meta del
field of view]per ogni raggio abbiamo un angolo diverso e una chiamata per
disegnare una colonna alla volta da sinistra a destra.
angle_step e' la differenza in radianti tra ogni raggio
*/
void	render_3d_view(t_game *game)
{
	t_render_3d_settings	settings;
	int						r;
	float					start_angle;
	float					current_angle;

	draw_floor_and_ceiling(game);
	init_render_3d_view(&settings);
	start_angle = game->player.angle - (settings.fov / 2.0f);
	r = 0;
	while (r < settings.num_rays)
	{
		current_angle = start_angle + r * settings.angle_step;
		draw_single_3d_ray(game, r, current_angle, &settings);
		r++;
	}
	update_gun_animation(game);
	draw_gun(game);
}

#endif

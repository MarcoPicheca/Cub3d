/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:13:42 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/17 17:35:56 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
ogni raggio ha il suo angolo, la sua direzione data da cos e sin,
il suo punto di impatto e il suo muro colpito
*/
void	init_render_3d_prop(t_3d_properties *prop, float angle)
{
	prop->ray_angle = angle;
	prop->ray_dir_x = cosf(angle);
	prop->ray_dir_y = sinf(angle);
	prop->hit_x = 0.0f;
	prop->hit_y = 0.0f;
	prop->side_local = 0;
}

/*
inizializzazione del rendering 3d
center_ray ci serve per il mirino
num_ray e' WIN_WIDTH perche ogni colonna rappresenta un raggio
angle_step e' la differena in radianti tra due raggi
*/
void	init_render_3d_view(t_render_3d_settings *settings)
{
	settings->fov = PI * 0.33f;
	settings->num_rays = WIN_WIDTH;
	settings->angle_step = settings->fov / (float)settings->num_rays;
	settings->center_ray = settings->num_rays * 0.5f;
}

/*
inizializza valori.
calcola la distanza, inoltre cast_ray_dda_side calcola i punti x e y
di collisione col muro [per singolo raggio] e il lato colpito.
correzione della distanza.
calcola l'altezza del muro (proporzionale alla distanza [divisione
 per correct_dist])[420 e' un valore arbitrario, piu e' grande 
piu il muro si alza], e top e bottom del muro.
sceglie la texture(nord,sud,ovest,est).
calcola la componente orizzontale della texture da mappare sul muro
step e' quanto avanzare nella texture in pixel per ogni riga del
 muro[puo dare sgranature]
*/
void	init_params_for_draw_single_3d_ray(t_draw_data *dd,
			t_3d_properties *prop, t_game *game)
{
	t_ray_result	result;

	dd->dist = cast_ray_dda_side(game, prop->ray_angle, &result);
	prop->hit_x = result.hit_x;
	prop->hit_y = result.hit_y;
	prop->side_local = result.side;
	dd->correct_dist = dd->dist * cosf(prop->ray_angle - game->player.angle);
	dd->wall_height = (int)((BLOCK * 420.0f) / dd->correct_dist);
	dd->wall_top = (WIN_HEIGHT / 2) - (dd->wall_height / 2);
	dd->wall_bot = dd->wall_top + dd->wall_height;
	dd->used_tex = pick_texture(game, prop);
	dd->tex_x = compute_tex_x(dd->used_tex, prop);
	dd->step = (float)dd->used_tex->height / (float)dd->wall_height;
}

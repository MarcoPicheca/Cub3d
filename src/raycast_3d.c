/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 01:35:27 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/26 19:22:56 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
inizializza parametri per ray casting
calcola la direzione nelle componenti x e y del raggio [cos e sin]
determina in che cella della griglia si trova il giocatore
se la componente x della direzione del raggio e' 0, il raggio non tagliera mai
un bordo verticale(2d) di una cella(continuera a muoversi lungo y), 1e30 e' un
approssimazione a infinito (stesso discorso per componente y), altrimenti 
(se non e' 0) viene calcolata come il reciproco del coseno(o seno) della
direzione del raggio [piu inclinazione piu tempo/distanza].
*/
void	init_ray_params2(t_ray_cast_params *params, t_game *game, float angle)
{
	params->ray_dir_x = cosf(angle);
	params->ray_dir_y = sinf(angle);
	params->map_x = (int)game->player.x;
	params->map_y = (int)game->player.y;
	if (params->ray_dir_x == 0)
		params->delta_dist_x = 1e30;
	else
		params->delta_dist_x = fabsf(1.0f / params->ray_dir_x);
	if (params->ray_dir_y == 0)
		params->delta_dist_y = 1e30;
	else
		params->delta_dist_y = fabsf(1.0f / params->ray_dir_y);
}

/*
movimenti del raggio nelle 4 direzioni
quando il raggio si muove verso un bordo:
side_dist = distanza_dal_bordo * (tempo per attraversare una cella)
*/
void	init_ray_params(t_ray_cast_params *params, t_game *game, float angle)
{
	init_ray_params2(params, game, angle);
	if (params->ray_dir_x < 0)
	{
		params->step_x = -1;
		params->side_dist_x = (game->player.x - params->map_x)
			* params->delta_dist_x;
	}
	else
	{
		params->step_x = 1;
		params->side_dist_x = ((params->map_x + 1.0f) - game->player.x)
			* params->delta_dist_x;
	}
	if (params->ray_dir_y < 0)
	{
		params->step_y = -1;
		params->side_dist_y = (game->player.y - params->map_y)
			* params->delta_dist_y;
	}
	else
	{
		params->step_y = 1;
		params->side_dist_y = ((params->map_y + 1.0f) - game->player.y)
			* params->delta_dist_y;
	}
}

/*
algoritmo dda
+ imposta se abbiamo attraversato muro orizzontale o verticale
+ si ferma quando tocca un muro
*/
void	perform_dda(t_ray_cast_params *params, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (params->side_dist_x < params->side_dist_y)
		{
			params->side_dist_x += params->delta_dist_x;
			params->map_x += params->step_x;
			params->side_local = 0;
		}
		else
		{
			params->side_dist_y += params->delta_dist_y;
			params->map_y += params->step_y;
			params->side_local = 1;
		}
		if (game->map.mtx2[params->map_y][params->map_x] == '1'
			|| game->map.mtx2[params->map_y][params->map_x] == '2')
		{
			hit = 1;
			params->hit_tile = game->map.mtx2[params->map_y][params->map_x];
		}
	}
}

// Calcola la distanza effettiva del muro colpito dal raggio e il punto
//esatto di collisione.
void	calculate_hit_details(t_ray_cast_params *params, t_game *game)
{
	if (params->side_local == 0)
		params->perp_wall_dist = (params->map_x - game->player.x
				+ (1 - params->step_x) / 2) / params->ray_dir_x;
	else
		params->perp_wall_dist = (params->map_y - game->player.y
				+ (1 - params->step_y) / 2) / params->ray_dir_y;
	params->hit_x = (game->player.x + params->perp_wall_dist
			* params->ray_dir_x) * BLOCK;
	params->hit_y = (game->player.y + params->perp_wall_dist
			* params->ray_dir_y) * BLOCK;
}

//ritorna la distanza corretta
float	cast_ray_dda_side(t_game *game, float angle, t_ray_result *result)
{
	t_ray_cast_params	params;

	init_ray_params(&params, game, angle);
	perform_dda(&params, game);
	calculate_hit_details(&params, game);
	if (result)
	{
		result->hit_x = params.hit_x;
		result->hit_y = params.hit_y;
		result->side = params.side_local;
		result->tile = params.hit_tile;
	}
	return (params.perp_wall_dist * BLOCK);
}

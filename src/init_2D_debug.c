/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2D_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:16:43 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/17 17:26:00 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
moltiplico posizione giocatore * BLOCK per sapere da dove deve partire il raggio
0.5 e' quanto deve avanzare il raggio ad ogni iterazione per il suo tracciamento
coseno-> quanto ci spostiamo nella componente orizzontale x
seno-> quanto in quella verticale. per entrambe usiamo step_size(quanto avanzare)
distance servira per la prospettiva
*/
void	init_cast(t_ray *ray, t_game *game, float *angle)
{
	ray->x = game->player.x * BLOCK;
	ray->y = game->player.y * BLOCK;
	ray->step_size = 0.5f;
	ray->delta_x = cosf(*angle) * ray->step_size;
	ray->delta_y = sinf(*angle) * ray->step_size;
	ray->distance = 0.0f;
}

/*
Finche non tocca il muro il raggio avanza
salvo le coordinate in cui tocca il muro
*/
float	cast_ray_dda(t_game *game, float angle, float *hit_x, float *hit_y)
{
	t_ray	ray;

	init_cast(&ray, game, &angle);
	while (!touch(ray.x, ray.y, game))
	{
		ray.x += ray.delta_x;
		ray.y += ray.delta_y;
		ray.distance += ray.step_size;
	}
	if (hit_x && hit_y)
	{
		*hit_x = ray.x;
		*hit_y = ray.y;
	}
	return (ray.distance);
}

/*
angle_step creazione di raggi equidistanti in termini di angolo (fov / num_rays)
start_angle ovvero l'angolo a sinistra e' l'angolo centrale (visione frontale del
 giocatore) meno meta del fov ray_angle e' l'angolo del raggio corrente, parte 
dal primo a sinitra e si sposta a destra seguendo l'indice che viene moltiplicato
per angle_step ovvero di quanto si sposta l'angolo in radianti end_x e end_y sono
le coordinate in cui il raggio colpisce il muro, divido per block per capire in 
che punto della griglia sono, moltiplico per scale per il rendering sulla
finestrainfine c'e il delta delle componenti orizzontali e verticali divisi per
la distanza per normalizzare il passo/step del raggio (per avanzare in modo
proporzionato)
*/
void	init_rays_2d(t_rays_2d *rays, t_game *game, t_render_2d *values,
			int ray_index)
{
	rays->angle_step = values->fov / values->num_rays;
	rays->start_angle = game->player.angle - values->fov * 0.5f;
	rays->ray_angle = rays->start_angle + ray_index * rays->angle_step;
	rays->start_x = game->player.x * values->scale_x;
	rays->start_y = game->player.y * values->scale_y;
	rays->hit_x = 0;
	rays->hit_y = 0;
	rays->distance = cast_ray_dda(game, rays->ray_angle, &rays->hit_x,
			&rays->hit_y);
	rays->end_x = rays->hit_x / BLOCK * values->scale_x;
	rays->end_y = rays->hit_y / BLOCK * values->scale_y;
	rays->stepx = (rays->end_x - rays->start_x) / rays->distance;
	rays->stepy = (rays->end_y - rays->start_y) / rays->distance;
	rays->cx = rays->start_x;
	rays->cy = rays->start_y;
}

/*
solita operazione di normalizzazione, divido le grandezze della finestra
per la dimensione della griglia, per capire come mappare il gioco sulla finestra
fov = field of view
*/
void	init_render_2d(t_render_2d *params, t_game *game)
{
	(void)game;
	params->scale_x = (float)WIN_WIDTH / (float)game->map.width;
	params->scale_y = (float)WIN_HEIGHT / (float)game->map.height;
	params->player_size = 14;
	params->color_wall2d = 0x0000FF;
	params->color_ray = 0x00F00F;
	params->fov = PI * 0.33;
	params->num_rays = 242;
}

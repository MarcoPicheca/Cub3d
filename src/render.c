/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:20:15 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/08 16:12:31 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
inizializzazione del rendering 3d
center_ray ci serve per il mirino
num_ray e' WIN_WIDTH perche ogni colonna rappresenta un raggio
angle_step e' la differena in radianti tra due raggi
*/
void init_render_3d_view(t_render_3d_settings *settings)
{
    settings->fov = PI * 0.33f;
    settings->num_rays = WIN_WIDTH;
    settings->angle_step = settings->fov / (float)settings->num_rays;
    settings->center_ray = settings->num_rays * 0.5f;
}

/*
funzione per la resa 3d
l'angolo iniziale e' quello a sinistra[il centrale(player.angle) - la meta del field of view]
per ogni raggio abbiamo un angolo diverso e una chiamata per disegnare una colonna alla volta
da sinistra a destra. angle_step e' la differenza in radianti tra ogni raggio
*/
void render_3d_view(t_game *game)
{
    t_render_3d_settings settings;
    int r;
    float start_angle;
    float current_angle;


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
    draw_hands(game);
}

/*
solita operazione di normalizzazione, divido le grandezze della finestra
per la dimensione della griglia, per capire come mappare il gioco sulla finestra
fov = field of view
*/
void    init_render_2d(t_render_2d *params, t_game *game)
{
    params->scale_x = (float)WIN_WIDTH  / (float)game->map.width;
    params->scale_y = (float)WIN_HEIGHT / (float)game->map.height;
    params->player_size = 14;
    params->color_wall2d = 0x0000FF;
    params->color_ray = 0x00F00F;
    params->fov = PI * 0.33;
    params->num_rays = 242;
}

/*
con il tasto 'v' cambiamo modalita'
viene chiamata da game_loop che sta in mlx_loop_hook
*/
void render_map(t_game *game)
{
    t_render_2d values; 

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
        // clear_image(game);
        render_3d_view(game);
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:01:40 by marco             #+#    #+#             */
/*   Updated: 2025/01/15 21:09:01 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_ray_dda(t_game *game, float angle, int color)
{
	float	ray_x;
	float	ray_y;
	float	delta_x;
	float	delta_y;

	ray_x = game->player.x * BLOCK;
	ray_y = game->player.y * BLOCK;
	delta_x = cos(angle) * 0.5;
	delta_y = sin(angle) * 0.5;
	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, color, game);
		ray_x += delta_x;
		ray_y += delta_y;
	}
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(x + j, y + i, color, game);
			j++;
		}
		i++;
	}
}

// void draw_map(t_game *game, t_render_2d *params)
// {
// 	int y = 0;
// 	int x;

// 	while (y < game->map.height)
// 	{
// 		x = 0;
// 		while (x < game->map.width)
// 		{
// 			if (game->map.mtx2[y][x] == '1')
// 				draw_square(x * params->square_size,y *
//	params->square_size, params->square_size, params->color_wall, game);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void draw_player(t_game *game, t_render_2d *params)
// {
// 	int square_size;
// 	int player_size;
// 	int color_player;
// 	int px;
// 	int py;

// 	square_size = params->square_size;
// 	color_player = params->color_player;
// 	player_size = params->player_size;
// 	px = game->player.x * square_size;
// 	py = game->player.y * square_size;
// 	draw_square(px - player_size / 2, py - player_size / 2,
//			player_size, color_player, game);
// }

// void draw_rays(t_game *game, t_render_2d *params)
// {
// 	float angle_step;
// 	float start_angle;
// 	float ray_angle;
// 	int i;

// 	angle_step = params->fov / params->num_rays;
// 	start_angle = game->player.angle - params->fov / 2;
// 	i = 0;
// 	while (i < params->num_rays)
// 	{
// 		ray_angle = start_angle + i * angle_step;
// 		draw_ray_dda(game, ray_angle, params->color_ray);
// 		i++;
// 	}
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:16:37 by marco             #+#    #+#             */
/*   Updated: 2025/01/07 17:17:05 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return true;
	return (game->map.mtx2[y][x] == '1' || 
			game->map.mtx2[(int)((py + 0.42) / BLOCK)][x] == '1' ||
			game->map.mtx2[y][(int)((px + 0.42) / BLOCK)] == '1');
}

void put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return;
	int index = y * game->line_size + x * (game->bpp / 8);
	game->img_data[index] = color & 0xFF;            
	game->img_data[index + 1] = (color >> 8) & 0xFF;  
	game->img_data[index + 2] = (color >> 16) & 0xFF;
}

void clear_image(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void    init_render_2d(t_render_2d *params)
{
	params->square_size = BLOCK;
	params->player_size = 20;
	params->color_wall = 0x0000FF;
	params->color_player = 0xFF0000;
	params->color_ray = 0x00FFF0;
	params->fov = PI / 3;
	params->num_rays = WIN_WIDTH;
}

void render_map(t_game *game)
{
	t_render_2d params; 

	init_render_2d(&params);
	clear_image(game);
	draw_map(game, &params);
	draw_player(game, &params);
	draw_rays(game, &params);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

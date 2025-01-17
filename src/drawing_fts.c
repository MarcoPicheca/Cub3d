/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_fts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:01:40 by marco             #+#    #+#             */
/*   Updated: 2025/01/17 17:03:17 by tschetti         ###   ########.fr       */
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

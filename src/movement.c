/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:57:59 by marco             #+#    #+#             */
/*   Updated: 2025/01/10 11:18:25 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void    set_angles_on_rotation(t_play *player)
// {
// 	if (player->left_rotate)
// 		player->angle -= player->angle_speed;
// 	if (player->right_rotate)
// 		player->angle += player->angle_speed;
// 	if (player->angle > 2 * PI)
// 		player->angle -= 2 * PI;
// 	if (player->angle < 0)
// 		player->angle += 2 * PI;
// }

// void    update_position(t_play *player, t_map *map, float move_x, float move_y)
// {
// 	float new_x = player->x + move_x / BLOCK;
// 	float new_y = player->y + move_y / BLOCK;
// 	float radius = 0.05; // Raggio attorno al giocatore

// 	if (map->mtx2[(int)(new_y - radius)][(int)(new_x)] == '1' || 
// 		map->mtx2[(int)(new_y + radius)][(int)(new_x)] == '1' ||
// 		map->mtx2[(int)(new_y)][(int)(new_x - radius)] == '1' ||
// 		map->mtx2[(int)(new_y)][(int)(new_x + radius)] == '1')
// 		return;//blocca giocatore se tocca muro
// 	player->x = new_x;
// 	player->y = new_y;
// }

// TODO da togliere?
// void update_position(t_play *player, t_map *map, float move_x, float move_y)
// {
//     float new_x = player->x + move_x / BLOCK;
//     float new_y = player->y + move_y / BLOCK;
//     float radius = 0.3;

//     if (map->mtx2[(int)new_y][(int)new_x] == '1')
//         return;
//     player->x = new_x;
//     player->y = new_y;
	
// }

// void    move_player(t_play *player, t_map *map)
// {
// 	float	cos_angle;
// 	float	sin_angle;

// 	cos_angle = cos(player->angle);
// 	sin_angle = sin(player->angle);
// 	set_angles_on_rotation(player);
// 	if (player->key_up)
// 		update_position(player, map, cos_angle * player->move_speed, sin_angle * player->move_speed);
// 	if (player->key_down)
// 		update_position(player, map, -cos_angle * player->move_speed, -sin_angle * player->move_speed);
// 	if (player->key_left)
// 		update_position(player, map, sin_angle * player->move_speed, -cos_angle * player->move_speed);
// 	if (player->key_right)
// 		update_position(player, map, -sin_angle * player->move_speed, cos_angle * player->move_speed);
// }

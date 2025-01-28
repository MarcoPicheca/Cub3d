/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:05:05 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/26 18:59:05 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// resta sempre tra 0 e 2𝜋
void	normalize_angle(float *angle)
{
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
}

/*
aggiorna l'angolo di rotazione del giocatore in base alla
velocita angolare (angle_speed) e al tasto premuto:
destra senso orario, sinistra antiorario
*/
void	set_angles_on_rotation(t_play *player)
{
	float	*angle;
	float	*angle_speed;

	angle = &player->angle;
	angle_speed = &player->angle_speed;
	if (player->left_rotate)
		*angle -= *angle_speed;
	if (player->right_rotate)
		*angle += *angle_speed;
	normalize_angle(angle);
}

/*
aggiunge un raggio attorno al giocatore per dargli "spessore", evitando
che oltrepassi blocchi messi in diagonale ad esempio.
se il movimento e' possibile aggiorna la posizione altrimenti ritorna al
chiamante. divido per block per passare dalle coordinate di mondo alle
coordinate della griglia.la condizione controlla che non ci si avvicini
troppo al muro nelle 4 direzioni, se non siamo troppo vicini aggiorna
la posizione
*/
void	update_position(t_play *player, t_map *map, float move_x, float move_y)
{
	float	new_x;
	float	new_y;
	float	radius;

	new_x = player->x + move_x / BLOCK;
	new_y = player->y + move_y / BLOCK;
	radius = 0.03;
	if (map->mtx2[(int)(new_y - radius)][(int)(new_x)] == '1'
		|| map->mtx2[(int)(new_y - radius)][(int)(new_x)] == '2'
		|| map->mtx2[(int)(new_y + radius)][(int)(new_x)] == '1'
		|| map->mtx2[(int)(new_y + radius)][(int)(new_x)] == '2'
		|| map->mtx2[(int)(new_y)][(int)(new_x - radius)] == '1'
		|| map->mtx2[(int)(new_y)][(int)(new_x - radius)] == '2'
		|| map->mtx2[(int)(new_y)][(int)(new_x + radius)] == '1'
		|| map->mtx2[(int)(new_y)][(int)(new_x + radius)] == '2')
		return ;
	player->x = new_x;
	player->y = new_y;
}

/*
muove il giocatore a,s,w,d
cos e sin per calcolare le componenti orizzontale e verticale
move_speed e' semplicemente la velocita' di movimento
*/
void	move_player(t_play *player, t_map *map)
{
	float	cos_angle;
	float	sin_angle;
	float	*move_speed;
	float	*angle;

	angle = &player->angle;
	move_speed = &player->move_speed;
	cos_angle = cos(*angle);
	sin_angle = sin(*angle);
	set_angles_on_rotation(player);
	if (player->key_up)
		update_position(player, map, cos_angle * (*move_speed),
			sin_angle * (*move_speed));
	if (player->key_down)
		update_position(player, map, -cos_angle * (*move_speed),
			-sin_angle * (*move_speed));
	if (player->key_left)
		update_position(player, map, sin_angle * (*move_speed),
			-cos_angle * (*move_speed));
	if (player->key_right)
		update_position(player, map, -sin_angle * (*move_speed),
			cos_angle * (*move_speed));
}

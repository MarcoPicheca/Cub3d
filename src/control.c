/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:07:51 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/15 20:42:37 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
 Verifica se una posizione continua (coordinate in pixel o mondo)
 si trova in un muro o nel suo intorno nella mappa discreta (griglia).
 L'offset +0.42 aggiunge un margine per gestire casi limite,
 come quando il raggio attraversa blocchi diagonali o per evitare
 perdita d'informazione nel passaggio da float a int.
 */
bool	touch(float px, float py, t_game *game)
{
	int	x;
	int	y;

	x = (int)(px / BLOCK);
	y = (int)(py / BLOCK);
	return (game->map.mtx2[y][x] == '1'
		|| game->map.mtx2[(int)((py + 0.42) / BLOCK)][x] == '1'
		|| game->map.mtx2[y][(int)((px + 0.42) / BLOCK)] == '1' );
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:07:51 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/17 17:33:53 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	count_map_dimensions(t_map *map)
{
	int	y;
	int	row_len;
	int	max_len;

	y = 0;
	max_len = 0;
	while (map->mtx2[y] != NULL)
	{
		row_len = ft_strlen(map->mtx2[y]);
		if (row_len > max_len)
			max_len = row_len;
		y++;
	}
	map->height = y;
	map->width = max_len;
}

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

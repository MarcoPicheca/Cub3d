/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:41:59 by marco             #+#    #+#             */
/*   Updated: 2025/01/07 17:59:05 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char    **copy_map_in_mtx2(t_map *map)
{
	static  int i = 0;
	char		**mtx2;

	mtx2 = ft_calloc(map->len_map, sizeof(char *));
	while (map->mtx[i] && i < map->len_map)
	{
		mtx2[i] = ft_strtrim(map->mtx[i], "\n");
		i++;
	}
	mtx2[i] = NULL;
    free_matrix2(map->mtx);
	return (mtx2);
}

// ang goes from 0.5 to 2 * Pi const to get the right angle
static	void	player_angle(float ang, t_play *player, t_map *map)
{
	player->x = map->x + 0.5;
	player->y = map->y + 0.5;
	player->angle = ang * PI;
}

int	init_map(t_map *map, t_play *player)
{
	map->mtx2 = copy_map_in_mtx2(map);
	map->x = 0;
	map->y = 0;
	while (map->mtx2[map->y] && map->y < map->len_map)
	{
		while (map->mtx2[map->y][map->x] != '\0')
		{
			if (map->mtx2[map->y][map->x] == 'S')
				return (player_angle(0.5, player, map), 0);
			if (map->mtx2[map->y][map->x] == 'W')
				return (player_angle(1, player, map), 0);
			if (map->mtx2[map->y][map->x] == 'N')
				return (player_angle(1.5, player, map), 0);
			if (map->mtx2[map->y][map->x] == 'E')
				return (player_angle(2, player, map), 0);
			map->x++;
		}
		map->y++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:41:59 by marco             #+#    #+#             */
/*   Updated: 2025/01/18 17:01:28 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//ho aggiunto + 1
char	**copy_map_in_mtx2(t_map *map)
{
	int			i;
	char		**mtx2;

	i = 0;
	mtx2 = ft_calloc(map->len_map + 1, sizeof(char *));
	if (!mtx2)
		return (NULL);
	while (i < map->len_map && map->mtx[i])
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

// void print_map_mtx2(t_map *map)
// {
//     int y = 0;
//     while (map->mtx2[y] != NULL)
//     {
//         printf("[%d] %s\n", y, map->mtx2[y]);
//         y++;
//     }
// }

void	switch_crdls(t_map *map)
{
	map->path_no = map->cardinals.path_n;
	map->path_so = map->cardinals.path_s;
	map->path_we = map->cardinals.path_w;
	map->path_ea = map->cardinals.path_e;
}

void	set_map_utils(t_map *map)
{
	map->mtx2 = copy_map_in_mtx2(map);
	count_map_dimensions(map);
	map->y = 0;
	switch_crdls(map);
	map->path_hands = "./textures/gun5.xpm";
	map->ceiling_color = (map->txt.cl_r << 16 | map->txt.cl_g << 8
			| map->txt.cl_b);
	map->floor_color = (map->txt.fl_r << 16 | map->txt.fl_g << 8
			| map->txt.fl_b);
}

int	init_map(t_map *map, t_play *player)
{
	set_map_utils(map);
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
		map->x = 0;
		map->y++;
	}
	return (0);
}

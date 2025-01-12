/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:41:59 by marco             #+#    #+#             */
/*   Updated: 2025/01/12 15:47:54 by mapichec         ###   ########.fr       */
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

//TODO usless sunction
// void	count_map_dimensions(t_map *map)
// {
// 	int	y;
// 	int	row_len;
// 	int	max_len;

// 	y = 0;
// 	max_len = 0;
// 	while(map->mtx2[y])
// 	{
// 		row_len = ft_strlen(map->mtx2[y]);
// 		if (row_len > max_len)
// 			max_len = row_len;
// 		y++;
// 	}
// 	map->height = y;
// 	map->width = max_len;
// }

void 	switch_crdls(t_map *map)
{
	map->path_no = map->cardinals.path_NO;
	map->path_so = map->cardinals.path_SO;
	map->path_we = map->cardinals.path_WS;
	map->path_ea = map->cardinals.path_EA;
}

int	init_map(t_map *map, t_play *player)
{
	map->mtx2 = copy_map_in_mtx2(map);
	// print_map_mtx2(map);
	// map->x = 0;
	map->y = 0;
	switch_crdls(map);
    // map->path_no = "./textures/paint.xpm";
    // map->path_so = "./textures/image.xpm";
    // map->path_we = "./textures/sb.xpm";
    // map->path_ea = "./textures/pb.xpm";
    map->path_hands = "./textures/gun5.xpm";
	map->ceiling_color = (map->txt.cl_r << 16 | map->txt.cl_g << 8 | map->txt.cl_b);
    map->floor_color = (map->txt.fl_r << 16 | map->txt.fl_g << 8 | map->txt.fl_b);
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

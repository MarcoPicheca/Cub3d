/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:16:58 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/17 17:18:14 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Usage: run it with a map\n"), 1);
	memset(&game, 0, sizeof(t_game));
	if (file_cub_check(av[1]))
		return (1);
	if (map_gen(&game, av[1]))
		return (1);
	init_map(&game.map, &game.player);
	init_game(&game);
	return (0);
}

// void init_map(t_map *map, t_play *player)
// {
//     const char *static_map[] = 
//     {
//         "111111111111111111111111",
//         "100000000000000000000001",
//         "10000N000010000000000001",
//         "111001011110000000000001",
//         "100000000000000000000001",
//         "100001000000010000000001",
//         "100010010000000111111101",
//         "100000000000000000000001",
//         "100001110000000011100001",
//         "111111 1111111111 111111"
//     };
//     map->ceiling_color = 0x222222;
//     map->floor_color = 0x333333;
//     map->width = 24;
//     map->height = 10;
//     map->path_no = "./textures/pb.xpm";
//     map->path_so = "./textures/image.xpm";
//     map->path_we = "./textures/sb.xpm";
//     map->path_ea = "./textures/rp.xpm";
//     map->path_hands = "./textures/gun5.xpm";
//     map->mtx2 = malloc(map->height * sizeof(char *));
//     if (!map->mtx2)
//         return;
//     for (int i = 0; i < map->height; i++)
//         map->mtx2[i] = ft_strdup(static_map[i]);
//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->width; x++)
//         {
//             if (map->mtx2[y][x] == 'S') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 0.5 * PI; //  1/2 𝜋  90°
//                 return;
//             }
//             if (map->mtx2[y][x] == 'w') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 1 * PI; //  𝜋  180°
//                 return;
//             }
//             if (map->mtx2[y][x] == 'N') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 1.5 * PI; //  3/2 𝜋  270°
//                 return;
//             }
//             if (map->mtx2[y][x] == 'E') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 2 * PI; //  2 𝜋  360°
//                 return;
//             }
//         }
//     }
// }

// int	look_for_width(t_map map)
// {
// 	int	result;	
// 	map.x = 0;
// 	map.y = 0;
// 	result = 0;
// 	while (map.mtx2[map.x])
// 	{
// 		map.y = ft_strlen(map.mtx2[map.x]);
// 		if (map.y > result)
// 			result = map.y;
// 		map.x++;
// 	}
// 	map.x = 0;
// 	map.y = 0;
// 	return (result);
// }

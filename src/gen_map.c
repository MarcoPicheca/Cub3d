/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:24:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/16 12:41:44 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static 	void	print_map(char **arr, int len)
{
	int	i = 0;

	while(i < len)
	{
		printf("%s", arr[i]);
		i++;
	}
}

static	void	free_matrix(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL && map[i][0] != '\0')
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

// static int	map_cardinali(t_map *map)
// {
// 	while(map->mtx[map->ht] && map->ht < INT_MAX)
// 	{
// 	}
// }

// divide la mappa in componenti (texture punti cardinali, texture floor e ceiling e mappa di gioco)
// e fa i vari check su di essi
// static int	map_div(t_map *map)
// {
	// if (map_cardinal(map))
	// 	return (free_matrix(map), 1);
// 	// // if (map_texture_f_c(map))
// 	// // 	return (free_matrix(map), 1);
// 	// // if (map_game(map))
// 	// // 	return (free_matrix(map), 1);
// 	return (0);
// }

static int	line_count(t_game *game)
{
	while (get_next_line(game->map.fd) != NULL)
		game->map.lines_ind++;
	close(game->map.fd);
	return (game->map.lines_ind + 1);
}

// genera la matrice della file della mappa
int	map_gen(t_game *game, char *av)
{
	t_map	*map_1;

	game->map.fd = -1;
	game->map.fd = open(av, O_RDONLY);
	if (game->map.fd == -1)
		return (1);
	game->map.mtx = (char **)ft_calloc(line_count(game), sizeof(char *));
	game->map.fd = open(av, O_RDONLY);
	if (!game->map.mtx)
		return (1);
	map_1 = &game->map;
	map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	if (!map_1->mtx[map_1->ht])
		return (free_matrix(map_1->mtx), 1);
	while (map_1->mtx[map_1->ht++] && map_1->ht < map_1->lines_ind)
		map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	close(game->map.fd);
	game->map.ht = 0;
	print_map(game->map.mtx, game->map.lines_ind);
	return (/*map_div(game->map.*/ 0);
}

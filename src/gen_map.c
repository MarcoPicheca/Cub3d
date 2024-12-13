/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:24:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/13 12:43:40 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static int	map_cardinali(t_map *map)
{
	while(map->mtx[map->ht] && map->mtx[map->ht] < INT_MAX)
	{
	}
}

// divide la mappa in componenti (texture punti cardinali, texture floor e ceiling e mappa di gioco)
// e fa i vari check su di essi
static int	map_div(t_map *map)
{
	if (map_cardinal(map))
		return (free_matrix(map), 1);
	if (map_texture_f_c(map))
		return (free_matrix(map), 1);
	if (map_game(map))
		return (free_matrix(map), 1);
	return (0);
}

// genera la matrice della file della mappa
int	map_gen(t_game *game, char *av)
{
	t_map	*map_1;

	game->map->fd = -1;
	game->map->fd = open(av, O_RDONLY);
	game->map->mtx = ft_calloc(INT_MAX, sizeof(char *));
	if (!game->map->mtx || game->map->fd == -1)
		return (1);
	map_1 = game->map;
	map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	if (!map_1->mtx[map_1->ht])
		return (free_matrix(map_1->mtx), 1);
	while (map_1->mtx[map_1->ht++] < INT_MAX)
	{
		map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
		if (!map_1->mtx[map_1->ht])
			return (free_matrix(map_1->mtx), 1);
	}
	game->map->lines_ind = game->map->ht;
	game->map->ht = 0;
	return (map_div(game->map));
}

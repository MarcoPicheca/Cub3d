/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:49:30 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/18 17:01:02 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_matrix(char **map, int len)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (i < len && map[i] && map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	free_matrix2(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map + i && map[i] && map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	map = NULL;
}

void	free_crlds(t_map *map)
{
	if (map->cardinals.path_n && map->cardinals.path_n != NULL)
		free(map->cardinals.path_n);
	if (map->cardinals.path_s && map->cardinals.path_s != NULL)
		free(map->cardinals.path_s);
	if (map->cardinals.path_e && map->cardinals.path_e != NULL)
		free(map->cardinals.path_e);
	if (map->cardinals.path_w && map->cardinals.path_w != NULL)
		free(map->cardinals.path_w);
}

void	free_txt(t_txt *txt)
{
	if (txt->path_txt_ceiling)
		free(txt->path_txt_ceiling);
	if (txt->path_txt_floor)
		free(txt->path_txt_floor);
}

// per tutte le allocazioni da freeare alla fine del gioco
void	free_game(t_game *game)
{
	if (game->map.mtx)
		free_matrix(game->map.mtx, game->map.lines_ind);
	if (game->map.cardinals.path_n != NULL
		|| game->map.cardinals.path_s != NULL
		|| game->map.cardinals.path_e != NULL
		|| game->map.cardinals.path_w != NULL)
		free_crlds(&game->map);
	free_txt(&game->map.txt);
}

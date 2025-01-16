/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:49:30 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/14 17:43:45 by mapichec         ###   ########.fr       */
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
	if (map->cardinals.path_NO && map->cardinals.path_NO != NULL)
		free(map->cardinals.path_NO);
	if (map->cardinals.path_SO && map->cardinals.path_SO != NULL)
		free(map->cardinals.path_SO);
	if (map->cardinals.path_EA && map->cardinals.path_EA != NULL)
		free(map->cardinals.path_EA);
	if (map->cardinals.path_WS && map->cardinals.path_WS != NULL)
		free(map->cardinals.path_WS);
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
	if (game->map.cardinals.path_NO != NULL
		|| game->map.cardinals.path_SO != NULL
		|| game->map.cardinals.path_EA != NULL
		|| game->map.cardinals.path_WS != NULL)
		free_crlds(&game->map);
	free_txt(&game->map.txt);
}

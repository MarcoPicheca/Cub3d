/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:49:30 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/16 17:11:52 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_matrix(char **map)
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

static	void	free_crlds(t_crdls *cards)
{
	if (map->cardinals.path_NO != NULL)
		free(map->cardinals.path_NO);
	if (map->cardinals.path_SO != NULL)
		free(map->cardinals.path_SO);
	if (map->cardinals.path_EA != NULL)
		free(map->cardinals.path_EA);
	if (map->cardinals.path_WS != NULL)
		free(map->cardinals.path_WS);
}

// per tutte le allocazioni da freeare alla fine del gioco
void	free_game(t_game *game)
{
	if (game->map.mtx)
		free_matrix(game->map.mtx);
	if (game->map.cardinals.path_NO == NULL || game->map.cardinals.path_SO == NULL
		|| game->map.cardinals.path_EA == NULL || game->map.cardinals.path_WS == NULL)
		free_crlds(&game->map.cardinals);
}

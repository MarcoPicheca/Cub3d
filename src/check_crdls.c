/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_crdls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:17:40 by marco             #+#    #+#             */
/*   Updated: 2025/01/04 10:37:56 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// check sui percorsi dei cardinali
static	int	check_paths_crld(t_crdls *crlds)
{
	crlds->path_NO = ft_strtrim2(crlds->path_NO, " \n");
	crlds->path_SO = ft_strtrim2(crlds->path_SO, " \n");
	crlds->path_EA = ft_strtrim2(crlds->path_EA, " \n");
	crlds->path_WS = ft_strtrim2(crlds->path_WS, " \n");
	// if (file_path(crlds->path_NO) || file_path(crlds->path_SO)
	// 	|| file_path(crlds->path_EA) || file_path(crlds->path_WS))
	// 	return (1);
	return (0);
}

// cicla finche allmeno una delle map->cardinals.path_* sono NULL e finche' la
// la mtx esiste, controllando che non ci sia l'inizio della mappa di gioco
int	map_cardinal(t_map *map)
{
	while(map->mtx[map->ht] && map->ht < map->lines_ind
		&& (map->cardinals.path_NO == NULL || map->cardinals.path_SO == NULL
		|| map->cardinals.path_EA == NULL || map->cardinals.path_WS == NULL))
	{
		if (err_game_card(map))
			return (1);
		if (ft_strncmp(map->mtx[map->ht], "NO ", 2) == 0
				&& map->cardinals.path_NO == NULL)
			map->cardinals.path_NO = ft_strdup(map->mtx[map->ht] + 3);
		if (ft_strncmp(map->mtx[map->ht], "SO ", 2) == 0
				&& map->cardinals.path_SO == NULL)
			map->cardinals.path_SO = ft_strdup(map->mtx[map->ht] + 3);
		if (ft_strncmp(map->mtx[map->ht], "EA ", 2) == 0
				&& map->cardinals.path_EA == NULL)
			map->cardinals.path_EA = ft_strdup(map->mtx[map->ht] + 3);
		if (ft_strncmp(map->mtx[map->ht], "WE ", 2) == 0
				&& map->cardinals.path_WS == NULL)
			map->cardinals.path_WS = ft_strdup(map->mtx[map->ht] + 3);
		map->ht++;
	}
	if (map->cardinals.path_NO == NULL || map->cardinals.path_SO == NULL
		|| map->cardinals.path_EA == NULL || map->cardinals.path_WS == NULL
		|| check_paths_crld(&map->cardinals))
		return (1);
	return (0);
}

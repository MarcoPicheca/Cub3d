/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_crdls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:17:40 by marco             #+#    #+#             */
/*   Updated: 2025/01/18 18:07:49 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// check sui percorsi dei cardinali
static	int	check_paths_crld(t_crdls *crlds)
{
	crlds->path_n = ft_strtrim2(crlds->path_n, " \n");
	crlds->path_s = ft_strtrim2(crlds->path_s, " \n");
	crlds->path_e = ft_strtrim2(crlds->path_e, " \n");
	crlds->path_w = ft_strtrim2(crlds->path_w, " \n");
	if (file_path(crlds->path_n) || file_path(crlds->path_s)
		|| file_path(crlds->path_e) || file_path(crlds->path_w))
		return (1);
	return (0);
}

// cicla finche allmeno una delle map->cardinals.path_* sono NULL e finche' la
// la mtx esiste, controllando che non ci sia l'inizio della mappa di gioco
int	map_cardinal(t_map *map)
{
	while (map->mtx[map->ht] && map->ht < map->lines_ind
		&& (map->cardinals.path_n == NULL || map->cardinals.path_s == NULL
			|| map->cardinals.path_e == NULL || map->cardinals.path_w == NULL))
	{
		if (err_game_card(map))
			return (1);
		if (ft_strncmp(map->mtx[map->ht], "NO ", 2) == 0
			&& map->cardinals.path_n == NULL)
			map->cardinals.path_n = ft_strdup(map->mtx[map->ht] + 3);
		if (ft_strncmp(map->mtx[map->ht], "SO ", 2) == 0
			&& map->cardinals.path_s == NULL)
			map->cardinals.path_s = ft_strdup(map->mtx[map->ht] + 3);
		if (ft_strncmp(map->mtx[map->ht], "EA ", 2) == 0
			&& map->cardinals.path_e == NULL)
			map->cardinals.path_e = ft_strdup(map->mtx[map->ht] + 3);
		if (ft_strncmp(map->mtx[map->ht], "WE ", 2) == 0
			&& map->cardinals.path_w == NULL)
			map->cardinals.path_w = ft_strdup(map->mtx[map->ht] + 3);
		map->ht++;
	}
	if (map->cardinals.path_n == NULL || map->cardinals.path_s == NULL
		|| map->cardinals.path_e == NULL || map->cardinals.path_w == NULL
		|| check_paths_crld(&map->cardinals))
		return (1);
	return (0);
}

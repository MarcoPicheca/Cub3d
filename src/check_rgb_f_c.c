/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_f_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:27:35 by marco             #+#    #+#             */
/*   Updated: 2025/01/19 16:06:17 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	map_texture_f_c(t_map *map)
{
	while (map->mtx[map->ht] && map->ht < map->lines_ind
		&& (map->txt.path_txt_floor == NULL
			|| map->txt.path_txt_ceiling == NULL))
	{
		if (err_game_card(map))
			return (1);
		if (ft_strncmp(map->mtx[map->ht], "F ", 1) == 0
			&& map->txt.path_txt_floor == NULL)
			map->txt.path_txt_floor = ft_strdup((map->mtx[map->ht] + 2));
		if (ft_strncmp(map->mtx[map->ht], "C ", 1) == 0
			&& map->txt.path_txt_ceiling == NULL)
			map->txt.path_txt_ceiling = ft_strdup((map->mtx[map->ht] + 2));
		map->ht++;
	}
	if (map->txt.path_txt_floor == NULL || map->txt.path_txt_ceiling == NULL
		|| check_rgb_txt(&map->txt))
		return (1);
	return (0);
}

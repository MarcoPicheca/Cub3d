/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_f_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:27:35 by marco             #+#    #+#             */
/*   Updated: 2025/01/18 18:02:31 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// controlla che il numero sia nel limite rgb 
static int	is_not_rgb(char *str)
{
	int	i;
	int	sum_digit;
	int	max_rgb;

	sum_digit = 0;
	i = 0;
	max_rgb = '2' + '5' + '5';
	if (str && ft_strlen(str) > 3)
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		sum_digit += str[i++];
	}
	if (sum_digit > max_rgb)
		return (1);
	return (0);
}

// conta il numero di componenti della matrice rgb
static	int	count_colors(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		if (is_not_rgb(tmp[i]))
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

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

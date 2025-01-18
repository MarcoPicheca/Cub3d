/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:42:59 by marco             #+#    #+#             */
/*   Updated: 2025/01/18 17:42:24 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// flood fill
void	map_isnt_close(int x, int y, char **tmp, int len)
{
	if (x < 0 || x > len - 1)
		return ;
	if (y < 0)
		return ;
	if (!tmp[x])
		return ;
	if (y >= ft_strlen(tmp[x]))
		return ;
	if (!tmp[x][y])
		return ;
	if (tmp[x][y] == '\0')
		return ;
	if (!ft_strchr_2("10NSEW", tmp[x][y]))
		return ;
	tmp[x][y] = 'C';
	map_isnt_close(x, y + 1, tmp, len);
	map_isnt_close(x, y - 1, tmp, len);
	map_isnt_close(x - 1, y, tmp, len);
	map_isnt_close(x + 1, y, tmp, len);
}

// mi sposta la y della mappa al primo carattere non spazio
void	move_to_first_char(char **tmp, t_map *map)
{
	while (tmp[map->x] && map->x < map->len_map)
	{
		map->y = 0;
		while (tmp[map->x][map->y] && tmp[map->x][map->y] != '\0'
			&& (ft_isspace(tmp[map->x][map->y]) || tmp[map->x][map->y] == '1'))
			map->y++;
		if (ft_strchr_2("0NSEW", tmp[map->x][map->y]))
			return ;
		map->x++;
	}
}

int	check_flood(char **tmp, int len)
{
	int	x;
	int	y;

	x = 0;
	while (x < len && tmp[x])
	{
		y = 0;
		while (tmp[x][y] != '\0' && tmp[x][y] != '\n')
		{
			if (!ft_isspace(tmp[x][y]) && tmp[x][y] != '\0'
				&& tmp[x][y] != 'C' && tmp[x][y] != '1')
				return (printf("Error!\n"));
			y++;
		}
		x++;
	}
	return (0);
}

// muove le coordinate al primo carattere '0NSWE', flood_fill e check_flood
int	flood_phil(t_map *map, char **tmp)
{
	map->ht = 0;
	move_to_first_char(tmp, map);
	map_isnt_close(map->x, map->y, tmp, map->len_map);
	if (check_flood(tmp, map->len_map))
		return (1);
	return (0);
}

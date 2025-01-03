/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:42:59 by marco             #+#    #+#             */
/*   Updated: 2024/12/24 16:35:17 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// flood fill
void	map_isnt_close(int x, int y, char **tmp, int len)
{
	if (x < 0 || x > len - 1)
	    return;
	if (y < 0)
	    return;
	if (!tmp[x])
	    return;
	if (!tmp[x][y])
	    return;
	if (tmp[x][y] == '\0')
	    return;
	if (!ft_strchr_2("10NSEW", tmp[x][y]))
	    return;
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
	y = 0;
	while (x < len && tmp[x])
	{
		while (tmp[x][y] != '\0' && tmp[x][y] != '\n')
		{
			if (!ft_isspace(tmp[x][y])
				&& tmp[x][y] != 'C' && tmp[x][y] != '1')
				return (printf("Error!\nMap is not closed!\n"));
			y++;	
		}
		x++;
	}
	return (0);
}


// TODO to be cancelled at the end or commented
// static 	void	print_map(char **arr, int len)
// {
// 	int	i = 0;

// 	while(i < len)
// 	{
// 		printf("%s", arr[i]);
// 		i++;
// 	}
// }

// muove le coordinate al primo carattere '0NSWE', flood_fill e check_flood
int	flood_phil(t_map *map, char **tmp)
{
	map->ht = 0;
	move_to_first_char(tmp, map);
	map_isnt_close(map->x, map->y, tmp, map->len_map);
	// print_map(tmp, map->len_map);
	printf("%s nord\n%s sud\n%s east\n%s ovest\n%s floor\n%s cieling\n", map->cardinals.path_NO,
	map->cardinals.path_SO, map->cardinals.path_EA, map->cardinals.path_WS, map->txt.path_txt_floor, map->txt.path_txt_ceiling);
	if (check_flood(tmp, map->len_map))
		return (1);
	return (0);
}

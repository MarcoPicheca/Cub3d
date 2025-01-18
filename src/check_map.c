/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:04:54 by marco             #+#    #+#             */
/*   Updated: 2025/01/18 18:39:14 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || line [i] == '\t'))
		i++;
	if (line[i] && line[i] == '\n')
		return (printf("Error!\n"));
	return (0);
}

// check se i char 0 hanno muri intorno a croce
static	int	zero_no_wall(char **tmp, t_map *map)
{
	int	i;

	i = 0;
	while (tmp[map->ht][i] != '\0')
	{
		if (tmp[map->ht][i] == '0')
		{
			if (i == 0 || map->ht == 0 || map->ht == (map->len_map - 1))
				return (printf("Error!\n"));
			if (ft_isspace(tmp[map->ht][i - 1]) || tmp[map->ht][i - 1] == '\0')
				return (printf("Error!\n"));
			if (ft_isspace(tmp[map->ht][i + 1]) || tmp[map->ht][i + 1] == '\n'
				|| tmp[map->ht][i + 1] == '\0')
				return (printf("Error!\n"));
			if (tmp[map->ht + 1] && (tmp[map->ht + 1][i] == '\n'
				|| ft_isspace(tmp[map->ht + 1][i])
				|| tmp[map->ht + 1][i] == '\0'))
				return (printf("Error!\n"));
			if (tmp[map->ht - 1] && (ft_isspace(tmp[map->ht - 1][i])
				|| tmp[map->ht - 1][i] == '\0' || tmp[map->ht + 1][i] == '\n'))
				return (printf("Error!\n"));
		}
		i++;
	}
	return (0);
}

static	void	copy_free_mtx(t_map *map)
{
	int		i;
	int		count;
	char	**tmp;

	count = map->start_map;
	i = 0;
	tmp = ft_calloc((map->end_map - map->start_map) + 1, sizeof(char *));
	while (map->mtx[count] && count < map->end_map)
	{
		tmp[i] = ft_strndup(map->mtx[count], ft_strlen(map->mtx[count]));
		i++;
		count++;
	}
	free_matrix(map->mtx, map->lines_ind);
	map->mtx = tmp;
}

// deve checkare che non ci siano linee vuote 
int	check_map_tmp(t_map *map)
{
	char		**tmp;
	static int	i = 0;

	tmp = ft_calloc((map->end_map - map->start_map) + 1, sizeof(char *));
	if (!tmp)
		return (perror("calloc tmp map_game\n"), 1);
	map->ht = map->start_map;
	while (i < map->len_map)
	{
		tmp[i] = ft_strdup(map->mtx[map->ht++]);
		i++;
	}
	map->ht = 0;
	while (tmp[map->ht] && map->ht < map->len_map)
	{
		if (line_is_empty(tmp[map->ht]) || zero_no_wall(tmp, map))
			return (free_matrix(tmp, map->len_map), 1);
		map->ht++;
	}
	if (flood_phil(map, tmp))
		return (free_matrix(tmp, map->len_map), 1);
	copy_free_mtx(map);
	return (free_matrix(tmp, map->len_map), 0);
}

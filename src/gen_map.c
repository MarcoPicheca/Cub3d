/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:24:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/11 18:34:59 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	void	free_matrix(char **map)
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

int	map_gen(t_game *game, char *av)
{
	t_map	*map_1;

	game->map->fd = -1;
	game->map->fd = open(av, O_RDONLY);
	game->map->mtx = ft_calloc(WIN_HEIGHT, sizeof(char *));
	if (!game->map->mtx || game->map->fd == -1)
		return (1);
	map_1 = game->map;
	map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	while (map_1->mtx[map_1->ht] && map_1->ht < 720)
	{
		if (ft_strlen(map_1->mtx[map_1->ht]) > 1280)
		{
			free_matrix(map_1->mtx);
			return (1);
		}
		printf("%s\n", map_1->mtx[map_1->ht]);
		map_1->mtx[++map_1->ht] = get_next_line(map_1->fd);
	}
	return (0);
}

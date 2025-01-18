/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:24:58 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/18 17:36:07 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// conta le linee del file per l'allocazione
static int	line_count(t_game *game)
{
	char	*tmp;

	tmp = get_next_line(game->map.fd);
	if (tmp != NULL)
		game->map.lines_ind++;
	while (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
		tmp = get_next_line(game->map.fd);
		if (tmp != NULL)
			game->map.lines_ind++;
	}
	if (tmp != NULL)
		free(tmp);
	close(game->map.fd);
	return (game->map.lines_ind + 1);
}

// genera la matrice dal file della mappa
int	map_gen(t_game *game, char *av)
{
	t_map	*map_1;

	game->map.fd = -1;
	game->map.fd = open(av, O_RDONLY);
	if (game->map.fd == -1)
		return (1);
	game->map.mtx = (char **)ft_calloc(line_count(game), sizeof(char *));
	game->map.fd = open(av, O_RDONLY);
	if (!game->map.mtx)
		return (1);
	map_1 = &game->map;
	map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	if (!map_1->mtx[map_1->ht])
		return (free_matrix(map_1->mtx, map_1->lines_ind), 1);
	while (map_1->mtx[map_1->ht++] && map_1->ht < map_1->lines_ind + 1)
		map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	close(map_1->fd);
	game->map.ht = 0;
	if (map_div(&game->map, game))
		return (free_game(game), 1);
	return (0);
}

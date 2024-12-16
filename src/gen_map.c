/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 18:24:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/16 17:02:53 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static 	void	print_map(char **arr, int len)
// {
// 	int	i = 0;

// 	while(i < len)
// 	{
// 		printf("%s", arr[i]);
// 		i++;
// 	}
// }
	// 	while (map->mtx[map->ht][map->wh] != '\0')

// checkka i char '1' e '0' sulla linea
static int	err_game_card(t_map *map)
{
	int	i;
	
	i = 0;
	while (map->mtx[map->ht][i] != '\0')
	{
		if (map->mtx[map->ht][i] == '1'
			|| map->mtx[map->ht][i] == '0')
			return (1);
		else if (map->mtx[map->ht][i] == '\t'
			|| map->mtx[map->ht][i] == ' ')
			i++;
		else
			return (0);
	}
	return (0);
}

// cicla finche allmeno una delle map->cardinals.path_* sono NULL e finche' la
// la mtx esiste, controllando che non ci sia l'inizio della mappa di gioco
static int	map_cardinal(t_map *map)
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
		|| map->cardinals.path_EA == NULL || map->cardinals.path_WS == NULL)
		return (1);
	return (0);
}

// divide la mappa in componenti (texture punti cardinali, texture floor e ceiling e mappa di gioco)
// e fa i vari check su di essi
static int	map_div(t_map *map)
{
	if (map_cardinal(map))
		return (1);
	// // if (map_texture_f_c(map))
	// // 	return (free_matrix(map), 1);
	// // if (map_game(map))
	// // 	return (free_matrix(map), 1);
	return (0);
}

static int	line_count(t_game *game)
{
	while (get_next_line(game->map.fd) != NULL)
		game->map.lines_ind++;
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
		return (free_matrix(map_1->mtx), 1);
	while (map_1->mtx[map_1->ht++] && map_1->ht < map_1->lines_ind)
		map_1->mtx[map_1->ht] = get_next_line(map_1->fd);
	close(game->map.fd);
	game->map.ht = 0;
	// print_map(game->map.mtx, game->map.lines_ind);
	if (map_div(&game->map))
		return (free_game(game), 1);
	return (0);
}

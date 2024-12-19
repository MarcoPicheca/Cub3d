/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:29:24 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/19 19:33:49 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// checkka i char '1' e '0' sulla linea
int	err_game_card(t_map *map)
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

int map_texture_f_c(t_map *map)
{
    while (map->mtx[map->ht] && map->ht < map->lines_ind
        && (map->txt.path_txt_floor == NULL || map->txt.path_txt_ceiling == NULL))
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
    if (map->txt.path_txt_floor == NULL || map->txt.path_txt_ceiling == NULL)
        return (1);
    return 0;
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
		|| map->cardinals.path_EA == NULL || map->cardinals.path_WS == NULL)
		return (1);
	return (0);
}

static	int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == 32 || line [i] == '\t'))
		i++;
	if (line[i] && line[i] == '\n')
		return (printf("Error!\nline is empty\n"));
	return (0);
}

static	int	zero_no_wall(char **tmp, t_map *map)
{
	int	i;

	i = 0;
	while (tmp[map->ht][i] != '\0')
	{
		if (tmp[map->ht][i] == '0')
		{
			if (i == 0)
				return (printf("Error!\nZero_no_wall!\n"));
			if (tmp[map->ht][i - 1] == 32 || tmp[map->ht][i - 1] == '\t' || tmp[map->ht][i - 1] == '\0')
				return (printf("Error!\nZero_no_wall!\n"));
			if (tmp[map->ht][i + 1] == 32 || tmp[map->ht][i + 1] == '\t'
				|| tmp[map->ht][i + 1] == '\n' || tmp[map->ht][i + 1] == '\0')
				return (printf("Error!\nZero_no_wall!\n"));
			if (tmp[map->ht + 1][i] == 32 || tmp[map->ht + 1][i] == '\t' || tmp[map->ht + 1][i] == '\0')
				return (printf("Error!\nZero_no_wall!\n"));
			if (tmp[map->ht - 1][i] == 32 || tmp[map->ht - 1][i] == '\t' || tmp[map->ht - 1][i] == '\0')
				return (printf("Error!\nZero_no_wall!\n"));
		}
		i++;
	}
	return (0);
}

// TODO da rifare
// int	wrong_spaces(char **tmp, t_map *map)
// {
// 	if (tmp[map->x] && map->x < map->len_map && tmp[map->x][map->y] != '\0')
// 	{
// 		if (tmp[map->x][map->y] && ft_isspace(tmp[map->x][map->y]))
// 		{
// 			if (tmp[map->x][map->y + 1] && ft_isspace(tmp[map->x][map->y + 1]))
// 			{
// 				map->y++;
// 				wrong_spaces(tmp, map);
// 			}
// 			if (tmp[map->x + 1][map->y] && ft_isspace(tmp[map->x + 1][map->y]))
// 			{
// 				map->x++;
// 				wrong_spaces(tmp, map);
// 			}
// 			if (tmp[map->x][map->y - 1] && ft_isspace(tmp[map->x][map->y - 1]))
// 			{
// 				map->y--;
// 				wrong_spaces(tmp, map);
// 			}
// 			if (tmp[map->x - 1][map->y] && ft_isspace(tmp[map->x - 1][map->y]))
// 			{
// 				map->x--;
// 				wrong_spaces(tmp, map);
// 			}
// 			else
// 				return (1);
// 			map->y++;
// 		}
// 		map->x++;
// 	}
// 	if (tmp[map->x][map->y] == '\0' && ft_isspace(tmp[map->x][map->y - 1]))
// 		return (1);
// 	return (0);
// }

/**
 *	1111111111111111111111111
	1000000000110000000000001
	1011000001110000000000001
	11111111111111111111111111
	11111111101100000111000001
								1
	100000000011000001110111111111111
	11110111111111011100000010001
	11110111111111011101010010001
	11000000110101011100000010001
	10000000000000001100000010001
	10000000000000001101010010001
	11000001110101011111011110N0111
	11110111 1110101 101111010001
	11111111 1111111 111111111111
 */

// deve checkare che non ci siano linee vuote 
static	int	check_map_tmp(t_map *map)
{	
	char		**tmp;
	static	int	i = 0;

	tmp = ft_calloc((map->end_map - map->start_map) + 1, sizeof(char *));
	if (!tmp)
		return (perror("calloc tmp map_game\n"), 1);
	map->ht = map->start_map;
	map->len_map = map->end_map - map->start_map + 1;
	while (i < map->len_map)
	{
		tmp[i] = ft_strdup(map->mtx[map->ht]);
		map->ht++;
		i++;
	}
	map->ht = 0;
	while (tmp[map->ht] && map->ht < map->len_map)
	{
		if (line_is_empty(tmp[map->ht]))
			return (printf("%s\n", tmp[map->ht]), free_matrix(tmp), 1);
		if (zero_no_wall(tmp, map))
			return (free_matrix(tmp), 1);
		map->ht++;
	}
	map->ht = 0;
	if (map_isnt_close(tmp, map))
			return (free_matrix(tmp), 1);
	return (0);
}

// parse mappa di gioco
int	map_game(t_map *map)
{
	while(map->mtx[map->ht] && map->ht < map->lines_ind)
	{
		if (err_game_card(map))
			break ;
		map->ht++;
	}
	map->start_map = map->ht;
	while(map->mtx[map->ht] && map->ht < map->lines_ind)
	{
		if (!err_game_card(map))
			break ;
		map->ht++;
	}
	// faccio +2 perche' deve contare sia la linea 
	// di start_map che quella di end
	map->end_map = map->lines_ind - map->start_map + 2;
	if (check_map_tmp(map))
		return (1);
	return (0);
}

// divide la mappa in componenti (texture punti cardinali, texture floor e ceiling e mappa di gioco)
// e fa i vari check su di essi
int	map_div(t_map *map)
{
	if (map_cardinal(map))
		return (printf("Error!\nerr cardinals!\n"), 1);
	map->ht = 0;
	if (map_texture_f_c(map))
		return (printf("Error!\nerr texture!\n"), 1);
	map->ht = 0;
	if (map_game(map))
		return (printf("Error!\nin game map!\n"), 1);
	return (0);
}

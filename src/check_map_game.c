/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:29:24 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/03 19:22:38 by marco            ###   ########.fr       */
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

// check se il file passato è una repo e check se il file è apriibile
int	file_path(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY | __O_DIRECTORY);
	if (fd != -1)
	{
		ft_printf("Error\nInvalid file!\n");
		close(fd);
		return (1);
	}
	close(fd);
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nInvalid open!\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

// TODO to be finished
int	check_main(t_map *map)
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

// parse mappa di gioco e definizione misure
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
	map->end_map = map->ht;
	map->len_map = map->end_map - map->start_map;
	if (check_map_tmp(map) || check_main(map))
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
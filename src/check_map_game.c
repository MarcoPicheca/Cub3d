/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_game.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:29:24 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/24 15:39:14 by marco            ###   ########.fr       */
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
		return (printf("Error!\nline is empty!\n"));
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
			if (tmp[map->ht + 1] && (tmp[map->ht + 1][i] == 32
				|| tmp[map->ht + 1][i] == '\t' || tmp[map->ht + 1][i] == '\0'))
				return (printf("Error!\nZero_no_wall!\n"));
			if (tmp[map->ht - 1][i] == 32 || tmp[map->ht - 1][i] == '\t' || tmp[map->ht - 1][i] == '\0')
				return (printf("Error!\nZero_no_wall!\n"));
		}
		i++;
	}
	return (0);
}

int	ft_strchr_2(char *s, int c)
{
	int		i;

	i = 0;
	if (c == 0)
		return (0);
	while (s[i] && s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] != (unsigned char)c)
		return (0);
	return (1);
}

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

// TODO to be cancelled at the end or commented
static 	void	print_map(char **arr, int len)
{
	int	i = 0;

	while(i < len)
	{
		printf("%s", arr[i]);
		i++;
	}
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
			if (!ft_isspace(tmp[x][y]) && tmp[x][y] != 'C' && tmp[x][y] != '1')
				return (printf("Error!\nMap is not closed!\n"));
			y++;	
		}
		x++;
	}
	return (0);
}

static int flood_phil(t_map *map, char **tmp)
{
	map->ht = 0;
	move_to_first_char(tmp, map);
	map_isnt_close(map->x, map->y, tmp, map->len_map);
	print_map(tmp, map->len_map);
	if (check_flood(tmp, map->len_map))
		return (1);
	return (0);
}

// deve checkare che non ci siano linee vuote 
static	int	check_map_tmp(t_map *map)
{	
	char		**tmp;
	static	int	i = 0;

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
	return (free_matrix(tmp, map->len_map), 0);
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

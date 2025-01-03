/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_f_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:27:35 by marco             #+#    #+#             */
/*   Updated: 2025/01/03 17:27:33 by marco            ###   ########.fr       */
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
	if (i > 3)
		return (1);
	return (0);
}

// riempie i campi rgb delle texture
static void fill_txt(t_txt *txt, char **cl, char **fl)
{
	txt->cl_r = ft_atoi(cl[0]);
	txt->cl_g = ft_atoi(cl[1]);
	txt->cl_b = ft_atoi(cl[2]);
	txt->fl_r = ft_atoi(fl[0]);
	txt->fl_g = ft_atoi(fl[1]);
	txt->fl_b = ft_atoi(fl[2]);
}

int	check_rgb_txt(t_txt *txt)
{
	static	int	i = 0;
	char		**tmp_cl;
	char		**tmp_fl;
	
	tmp_cl = NULL;
	tmp_fl = NULL;
	while (txt->path_txt_ceiling && txt->path_txt_ceiling[i])
	{
		if (txt->path_txt_ceiling[i] == ',' || txt->path_txt_ceiling[i] == '\t')
			txt->path_txt_ceiling[i] = 32;
		i++;
	}
	i = 0;
	while (txt->path_txt_floor && txt->path_txt_floor[i] != 0)
	{
		if (txt->path_txt_floor[i] == ',' || txt->path_txt_floor[i] == '\t')
			txt->path_txt_floor[i] = 32;
		i++;
	}
	txt->path_txt_ceiling = ft_strtrim2(txt->path_txt_ceiling, "\n");
	txt->path_txt_floor = ft_strtrim2(txt->path_txt_floor, "\n");
	tmp_cl = ft_split(txt->path_txt_ceiling, 32);
	tmp_fl = ft_split(txt->path_txt_floor, 32);
	if (count_colors(tmp_cl) || count_colors(tmp_fl))
		return (free_matrix(tmp_cl, 3), free_matrix(tmp_fl, 3), 1);
	return (fill_txt(txt, tmp_cl, tmp_fl), free_matrix(tmp_cl, 3), free_matrix(tmp_fl, 3), 0);
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
    if (map->txt.path_txt_floor == NULL || map->txt.path_txt_ceiling == NULL
		|| check_rgb_txt(&map->txt))
        return (1);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb_f_c_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:57:38 by marco             #+#    #+#             */
/*   Updated: 2025/01/18 18:08:25 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// riempie i campi rgb delle texture
static	void	fill_txt(t_txt *txt, char **cl, char **fl)
{
	txt->cl_r = ft_atoi(cl[0]);
	txt->cl_g = ft_atoi(cl[1]);
	txt->cl_b = ft_atoi(cl[2]);
	txt->fl_r = ft_atoi(fl[0]);
	txt->fl_g = ft_atoi(fl[1]);
	txt->fl_b = ft_atoi(fl[2]);
}

static	int	ft_check_rgb_txt_2(t_txt *txt)
{
	char		**tmp_cl;
	char		**tmp_fl;

	tmp_fl = NULL;
	tmp_cl = ft_split(txt->path_txt_ceiling, 32);
	if (!tmp_cl || *tmp_cl == NULL)
	{
		if (!tmp_cl)
			return (1);
		if (*tmp_cl == NULL)
			return (free(tmp_cl), 1);
	}
	tmp_fl = ft_split(txt->path_txt_floor, 32);
	if (!tmp_fl || *tmp_fl == NULL)
	{
		if (!tmp_fl)
			return (free_matrix(tmp_cl, 3), 1);
		if (*tmp_cl == NULL)
			return (free_matrix(tmp_cl, 3), free(tmp_fl), 1);
	}
	if (count_colors(tmp_cl) || count_colors(tmp_fl))
		return (free_matrix(tmp_cl, 3), free_matrix(tmp_fl, 3), 1);
	return (fill_txt(txt, tmp_cl, tmp_fl), free_matrix(tmp_cl, 3),
		free_matrix(tmp_fl, 3), 0);
}

int	check_rgb_txt(t_txt *txt)
{
	static int	i = 0;

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
	return (ft_check_rgb_txt_2(txt));
}

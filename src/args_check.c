/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:13:27 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/18 17:37:51 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_is_cub(char *str, int len, char *ext)
{
	int	i;

	i = 4;
	if (!str)
		return (1);
	while (i > 0)
	{
		if (str[len] != ext[i])
			return (0);
		i--;
		len--;
	}
	return (1);
}

// check se il file passato è una repo e 
// check se il file ha un estensione di tipo .cub
int	file_cub_check(char *str)
{
	int	i;
	int	fd;

	i = ft_strlen(str);
	fd = open(str, O_RDONLY | __O_DIRECTORY);
	if (!ft_is_cub(str, i, ".cub") && fd != -1)
	{
		ft_printf("Error\n");
		close(fd);
		return (1);
	}
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

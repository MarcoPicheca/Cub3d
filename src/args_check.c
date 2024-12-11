/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:13:27 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/11 15:17:49 by mapichec         ###   ########.fr       */
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

int	file_cub_check(char *str)
{
	int	i;
	int	fd;

	i = ft_strlen(str);
	fd = open(str, O_RDONLY | __O_DIRECTORY);
	if (!ft_is_cub(str, i, ".cub") || fd != -1)
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

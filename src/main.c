/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:16:58 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/07 17:19:04 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
		return (0);
	memset(&game, 0, sizeof(t_game));
	memset(&game.map, 0, sizeof(t_map));
	if (file_cub_check(av[1]))
		return (1);
	if (map_gen(&game, av[1]))
		return (1);
	init_map(&game.map, &game.player);
	init_game(&game);
	return (0);
}

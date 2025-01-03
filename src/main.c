/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:16:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/13 16:00:13 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Solo di prova per il momento non effettiva parte del prog
void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

int main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0);
	memset(&game, 0, sizeof(t_game));
	memset(&game.map, 0, sizeof(t_map));
	if (file_cub_check(av[1]))
		return (1);
	if (map_gen(&game, av[1]))
		return (1);
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}

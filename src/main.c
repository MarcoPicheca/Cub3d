/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:16:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/10 17:52:02 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

char	**parse_args()

int main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0);
	memset(&game, 0, sizeof(t_game));
	// parse
	game.map = parse_args(av);
	init_game(&game);
	mlx_loop(game.mlx);
	return (0);
}

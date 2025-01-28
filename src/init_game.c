/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:09:53 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/24 15:05:20 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_play *player)
{
	player->angle_speed = 0.042;
	player->move_speed = 7.42;
	player->render_mode = 1;
	player->minimap_view = 0;
	player->is_shooting = 0;
}

//bpp e' bit per pixel
//line_size e' larghezza in byte della riga
void	init_game(t_game *game)
{
	init_player(&game->player);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_size, &game->endian);
	load_textures(game);
	game->player.game = game;
	mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
	mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

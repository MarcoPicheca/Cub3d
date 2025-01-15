/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:18:50 by marco             #+#    #+#             */
/*   Updated: 2025/01/10 11:21:03 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// static	void	init_player(t_play *player)
// {
// 	player->angle_speed = 0.042; //radianti * (iterazioni mlx_loop)
//		 -- 0.042 = 3°circa
// 	player->move_speed = 4.2;    //pixel * (iterazioni mlx_loop)
// }

int	game_loop(t_game *game)
{
	move_player(&game->player, &game->map);
	render_map(game);
	return (0);
}

//bpp e' bit per pixel
//line_size e' larghezza in byte della riga
// void init_game(t_game *game)
// {
// 	init_player(&game->player);
// 	game->mlx = mlx_init();//server grafico
// 	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
// 	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	game->img_data = mlx_get_data_addr(game->img, &game->bpp, 
//				&game->line_size, &game->endian);//gestione pixel
// 	mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
// 	mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
// 	mlx_hook(game->win, 17, 0, close_window, game);
// 	mlx_loop_hook(game->mlx, game_loop, game);
// 	mlx_loop(game->mlx);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_callback_fts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:19:23 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/18 16:43:04 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	end_clean(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->win)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	free_matrix(game->map.mtx, game->map.len_map);
	free_crlds(&game->map);
	free_txt(&game->map.txt);
	exit(0);
}

void	exit_game(t_game *game)
{
	if (game->player.hands != NULL)
		mlx_destroy_image(game->mlx, game->player.hands);
	if (game->tex_hands.img != NULL)
		mlx_destroy_image(game->mlx, game->tex_hands.img);
	if (game->tex_ea.img != NULL)
		mlx_destroy_image(game->mlx, game->tex_ea.img);
	if (game->tex_no.img != NULL)
		mlx_destroy_image(game->mlx, game->tex_no.img);
	if (game->tex_so.img != NULL)
		mlx_destroy_image(game->mlx, game->tex_so.img);
	if (game->tex_we.img != NULL)
		mlx_destroy_image(game->mlx, game->tex_we.img);
	if (game->my_tex.img != NULL)
		mlx_destroy_image(game->mlx, game->my_tex.img);
	if (game->img != NULL)
		mlx_destroy_image(game->mlx, game->img);
	if (game->map.mtx2 != NULL)
		free_matrix(game->map.mtx2, game->map.len_map);
	if (game->map.mtx != NULL)
		free_matrix2(game->map.mtx);
	end_clean(game);
}

int	close_window(t_game *game)
{
	exit_game(game);
	return (0);
}

int	key_press(int keycode, t_play *player)
{
	if (keycode == W)
		player->key_up = 1;
	else if (keycode == S)
		player->key_down = 1;
	else if (keycode == A)
		player->key_left = 1;
	else if (keycode == D)
		player->key_right = 1;
	else if (keycode == LEFT)
		player->left_rotate = 1;
	else if (keycode == RIGHT)
		player->right_rotate = 1;
	else if (keycode == ESC)
		exit_game(player->game);
	else if (keycode == V)
		player->render_mode = !player->render_mode;
	else if (keycode == M)
		player->minimap_view = !player->minimap_view;
	return (0);
}

int	key_release(int keycode, t_play *player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == LEFT)
		player->left_rotate = 0;
	if (keycode == RIGHT)
		player->right_rotate = 0;
	return (0);
}

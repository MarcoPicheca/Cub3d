/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_callback_fts.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:19:23 by tschetti          #+#    #+#             */
/*   Updated: 2024/12/20 20:39:54 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int game_loop(t_game *game)
{
    move_player(&game->player, &game->map);
    render_map(game);
    return (0);
}

int key_press(int keycode, t_play *player)
{
    if (keycode == W)
        player->key_up = 1;
    if (keycode == S)
        player->key_down = 1;
    if (keycode == A)
        player->key_left = 1;
    if (keycode == D)
        player->key_right = 1;
    if (keycode == LEFT)
        player->left_rotate = 1;
    if (keycode == RIGHT)
        player->right_rotate = 1;
    if (keycode == ESC)
        exit(0);
    return (0);
}

int key_release(int keycode, t_play *player)
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
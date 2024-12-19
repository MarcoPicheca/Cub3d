/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:16:58 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/19 18:29:58 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

typedef struct s_render_params {
    int square_size;
    int player_size;
    int color_wall;
    int color_player;
    int color_ray;
    float fov;
    int num_rays;
} t_render_params;

bool touch(float px, float py, t_game *game)
{
    int x = px / BLOCK;
    int y = py / BLOCK;
    if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
        return true;
    return (game->map.mtx2[y][x] == '1');
}

void draw_ray_dda(t_game *game, float angle, int color)
{
    float ray_x = game->player.x * BLOCK; 
    float ray_y = game->player.y * BLOCK;
    float delta_x = cos(angle) * 0.5;
    float delta_y = sin(angle) * 0.5;

    while (!touch(ray_x, ray_y, game))
    {
        put_pixel(ray_x, ray_y, color, game);
        ray_x += delta_x;
        ray_y += delta_y;
    }
}

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
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

void put_pixel(int x, int y, int color, t_game *game)
{
    if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
        return;
    int index = y * game->line_size + x * (game->bpp / 8);
    game->img_data[index] = color & 0xFF;            
    game->img_data[index + 1] = (color >> 8) & 0xFF;  
    game->img_data[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
    int i = 0;
    int j;

    while (i < size)
    {
        j = 0; 
        while (j < size)
        {
            put_pixel(x + j, y + i, color, game);
            j++;
        }
        i++;
    }
}

void draw_map(t_game *game, t_render_params *params)
{
    int y = 0;
    int x;

    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.mtx2[y][x] == '1')
                draw_square(x * params->square_size, y * params->square_size, params->square_size, params->color_wall, game);
            x++;
        }
        y++;
    }
}

void clear_image(t_game *game)
{
    for(int y = 0; y < WIN_HEIGHT; y++)
        for(int x = 0; x < WIN_WIDTH; x++)
            put_pixel(x, y, 0, game);
}

void draw_player(t_game *game, t_render_params *params)
{
    int px = game->player.x * params->square_size;
    int py = game->player.y * params->square_size;
    draw_square(px - params->player_size / 2, py - params->player_size / 2, params->player_size, params->color_player, game);
}

void draw_rays(t_game *game, t_render_params *params)
{
    float angle_step = params->fov / params->num_rays;
    float start_angle = game->player.angle - params->fov / 2;
    int i = 0;

    while (i < params->num_rays)
    {
        float ray_angle = start_angle + i * angle_step;
        draw_ray_dda(game, ray_angle, params->color_ray);
        i++;
    }
}

void render_map(t_game *game)
{
    t_render_params params = 
    {
        .square_size = BLOCK,
        .player_size = 20,
        .color_wall = 0x0000FF,
        .color_player = 0xFF0000,
        .color_ray = 0x00FFF0,
        .fov = PI / 3,
        .num_rays = WIN_WIDTH
    };
    clear_image(game);
    draw_map(game, &params);
    draw_player(game, &params);
    draw_rays(game, &params);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}


void set_angles_on_rotation(t_play *player)
{
    if (player->left_rotate)
        player->angle -= player->angle_speed;
    if (player->right_rotate)
        player->angle += player->angle_speed;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;
}

void update_position(t_play *player, t_map *map, float move_x, float move_y)
{
    float new_x = player->x + move_x / BLOCK;
    float new_y = player->y + move_y / BLOCK;

    if (map->mtx2[(int)new_y][(int)new_x] != '1')
    {
        player->x = new_x;
        player->y = new_y;
    }
}

void move_player(t_play *player, t_map *map)
{
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    set_angles_on_rotation(player);
    if (player->key_up)
        update_position(player, map, cos_angle * player->move_speed, sin_angle * player->move_speed);
    if (player->key_down)
        update_position(player, map, -cos_angle * player->move_speed, -sin_angle * player->move_speed);
    if (player->key_left)
        update_position(player, map, sin_angle * player->move_speed, -cos_angle * player->move_speed);
    if (player->key_right)
        update_position(player, map, -sin_angle * player->move_speed, cos_angle * player->move_speed);
}

void init_player(t_play *player)
{
    player->angle_speed = 0.03;
    player->move_speed = 3.0;
}

int game_loop(t_game *game)
{
    move_player(&game->player, &game->map);
    render_map(game);
    return (0);
}

void init_game(t_game *game)
{
    init_player(&game->player);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->line_size, &game->endian);
    mlx_hook(game->win, 2, 1L << 0, key_press, &game->player);
    mlx_hook(game->win, 3, 1L << 1, key_release, &game->player);
    mlx_hook(game->win, 17, 0L, close_window, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
}

void init_map(t_map *map, t_play *player)
{
    const char *static_map[] = 
    {
        "1111111111",
        "1000000001",
        "1010100001",
        "1000N00001",
        "1010000001",
        "1000000101",
        "1001000011",
        "1000000011",
        "1111111111"
    };
    map->width = 10;
    map->height = 9;
    map->mtx2 = malloc(map->height * sizeof(char *));
    if (!map->mtx2)
        return;
    for (int i = 0; i < map->height; i++)
        map->mtx2[i] = ft_strdup(static_map[i]);

    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            if (map->mtx2[y][x] == 'N') 
            {
                player->x = x + 0.5;
                player->y = y + 0.5;
                player->angle = 1.5 * PI;
                return;
            }
        }
    }

}

int main(int ac, char **av)
{
    t_game game;
    (void)av;

    if (ac != 2)
    {
        printf("Usage: %s <map_file>\n", av[0]);
        return (1);
    }
    memset(&game, 0, sizeof(t_game));
    init_map(&game.map, &game.player);
    init_game(&game);
    return (0);
}

// int main(int ac, char **av)
// {
// 	t_game	game;

// 	if (ac != 2)
// 		return (0);
// 	memset(&game, 0, sizeof(t_game));
// 	memset(&game.map, 0, sizeof(t_map));
// 	if (file_cub_check(av[1]))
// 		return (1);
// 	if (map_gen(&game, av[1]))
// 		return (1);
// 	init_game(&game);
// 	mlx_loop(game.mlx);
// 	return (0);
// }

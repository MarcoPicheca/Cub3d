/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:16:58 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/15 15:47:47 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
moltiplico posizione giocatore * BLOCK per sapere da dove deve partire il raggio
0.5 e' quanto deve avanzare il raggio ad ogni iterazione per il suo tracciamento
coseno-> quanto ci spostiamo nella componente orizzontale x
seno-> quanto in quella verticale. per entrambe usiamo step_size(quanto avanzare)
distance servira per la prospettiva
*/
void	init_cast(t_ray *ray, t_game *game, float *angle)
{
	ray->x = game->player.x * BLOCK;
	ray->y = game->player.y * BLOCK;
	ray->step_size = 0.5f;
	ray->delta_x = cosf(*angle) * ray->step_size;
	ray->delta_y = sinf(*angle) * ray->step_size;
	ray->distance = 0.0f;
}

/*
Finche non tocca il muro il raggio avanza
salvo le coordinate in cui tocca il muro
*/
float	cast_ray_dda(t_game *game, float angle, float *hit_x, float *hit_y)
{
	t_ray	ray;

	init_cast(&ray, game, &angle);
	while (!touch(ray.x, ray.y, game))
	{
		ray.x += ray.delta_x;
		ray.y += ray.delta_y;
		ray.distance += ray.step_size;
	}
	if (hit_x && hit_y)
	{
		*hit_x = ray.x;
		*hit_y = ray.y;
	}
	return (ray.distance);
}

/*
angle_step creazione di raggi equidistanti in termini di angolo (fov / num_rays)
start_angle ovvero l'angolo a sinistra e' l'angolo centrale (visione frontale del
 giocatore) meno meta del fov ray_angle e' l'angolo del raggio corrente, parte 
dal primo a sinitra e si sposta a destra seguendo l'indice che viene moltiplicato
per angle_step ovvero di quanto si sposta l'angolo in radianti end_x e end_y sono
le coordinate in cui il raggio colpisce il muro, divido per block per capire in 
che punto della griglia sono, moltiplico per scale per il rendering sulla
finestrainfine c'e il delta delle componenti orizzontali e verticali divisi per
la distanza per normalizzare il passo/step del raggio (per avanzare in modo
proporzionato)
*/
void	init_rays_2d(t_rays_2d *rays, t_game *game, t_render_2d *values,
			int ray_index)
{
	rays->angle_step = values->fov / values->num_rays;
	rays->start_angle = game->player.angle - values->fov * 0.5f;
	rays->ray_angle = rays->start_angle + ray_index * rays->angle_step;
	rays->start_x = game->player.x * values->scale_x;
	rays->start_y = game->player.y * values->scale_y;
	rays->hit_x = 0;
	rays->hit_y = 0;
	rays->distance = cast_ray_dda(game, rays->ray_angle, &rays->hit_x,
			&rays->hit_y);
	rays->end_x = rays->hit_x / BLOCK * values->scale_x;
	rays->end_y = rays->hit_y / BLOCK * values->scale_y;
	rays->stepx = (rays->end_x - rays->start_x) / rays->distance;
	rays->stepy = (rays->end_y - rays->start_y) / rays->distance;
	rays->cx = rays->start_x;
	rays->cy = rays->start_y;
}

/*
ogni raggio ha il suo angolo, la sua direzione data da cos e sin,
il suo punto di impatto e il suo muro colpito
*/
void	init_render_3d_prop(t_3d_properties *prop, float angle)
{
	prop->ray_angle = angle;
	prop->ray_dir_x = cosf(angle);
	prop->ray_dir_y = sinf(angle);
	prop->hit_x = 0.0f;
	prop->hit_y = 0.0f;
	prop->side_local = 0;
}

/*
solita operazione di normalizzazione, divido le grandezze della finestra
per la dimensione della griglia, per capire come mappare il gioco sulla finestra
fov = field of view
*/
void	init_render_2d(t_render_2d *params, t_game *game)
{
	(void)game;
	params->scale_x = (float)WIN_WIDTH / (float)game->map.width;
	params->scale_y = (float)WIN_HEIGHT / (float)game->map.height;
	params->player_size = 14;
	params->color_wall2d = 0x0000FF;
	params->color_ray = 0x00F00F;
	params->fov = PI * 0.33;
	params->num_rays = 242;
}

/*
inizializzazione del rendering 3d
center_ray ci serve per il mirino
num_ray e' WIN_WIDTH perche ogni colonna rappresenta un raggio
angle_step e' la differena in radianti tra due raggi
*/
void	init_render_3d_view(t_render_3d_settings *settings)
{
	settings->fov = PI * 0.33f;
	settings->num_rays = WIN_WIDTH;
	settings->angle_step = settings->fov / (float)settings->num_rays;
	settings->center_ray = settings->num_rays * 0.5f;
}

/*
inizializza valori.
calcola la distanza, inoltre cast_ray_dda_side calcola i punti x e y
di collisione col muro [per singolo raggio] e il lato colpito.
correzione della distanza.
calcola l'altezza del muro (proporzionale alla distanza [divisione
 per correct_dist])[420 e' un valore arbitrario, piu e' grande 
piu il muro si alza], e top e bottom del muro.
sceglie la texture(nord,sud,ovest,est).
calcola la componente orizzontale della texture da mappare sul muro
step e' quanto avanzare nella texture in pixel per ogni riga del
 muro[puo dare sgranature]
*/
void	init_params_for_draw_single_3d_ray(t_draw_data *dd,
			t_3d_properties *prop, t_game *game)
{
	t_ray_result	result;

	dd->dist = cast_ray_dda_side(game, prop->ray_angle, &result);
	prop->hit_x = result.hit_x;
	prop->hit_y = result.hit_y;
	prop->side_local = result.side;
	dd->correct_dist = dd->dist * cosf(prop->ray_angle - game->player.angle);
	dd->wall_height = (int)((BLOCK * 420.0f) / dd->correct_dist);
	dd->wall_top = (WIN_HEIGHT / 2) - (dd->wall_height / 2);
	dd->wall_bot = dd->wall_top + dd->wall_height;
	dd->used_tex = pick_texture(game, prop);
	dd->tex_x = compute_tex_x(dd->used_tex, prop);
	dd->step = (float)dd->used_tex->height / (float)dd->wall_height;
}

void	init_player(t_play *player)
{
	player->angle_speed = 0.042;
	player->move_speed = 7.42;
	player->render_mode = 1;
	player->minimap_view = 0;
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

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (printf("Usage: run it with a map\n"), 1);
	memset(&game, 0, sizeof(t_game));
	if (file_cub_check(av[1]))
		return (1);
	if (map_gen(&game, av[1]))
		return (1);
	init_map(&game.map, &game.player);
	init_game(&game);
	return (0);
}

// void init_map(t_map *map, t_play *player)
// {
//     const char *static_map[] = 
//     {
//         "111111111111111111111111",
//         "100000000000000000000001",
//         "10000N000010000000000001",
//         "111001011110000000000001",
//         "100000000000000000000001",
//         "100001000000010000000001",
//         "100010010000000111111101",
//         "100000000000000000000001",
//         "100001110000000011100001",
//         "111111 1111111111 111111"
//     };
//     map->ceiling_color = 0x222222;
//     map->floor_color = 0x333333;
//     map->width = 24;
//     map->height = 10;
//     map->path_no = "./textures/pb.xpm";
//     map->path_so = "./textures/image.xpm";
//     map->path_we = "./textures/sb.xpm";
//     map->path_ea = "./textures/rp.xpm";
//     map->path_hands = "./textures/gun5.xpm";
//     map->mtx2 = malloc(map->height * sizeof(char *));
//     if (!map->mtx2)
//         return;
//     for (int i = 0; i < map->height; i++)
//         map->mtx2[i] = ft_strdup(static_map[i]);
//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->width; x++)
//         {
//             if (map->mtx2[y][x] == 'S') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 0.5 * PI; //  1/2 𝜋  90°
//                 return;
//             }
//             if (map->mtx2[y][x] == 'w') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 1 * PI; //  𝜋  180°
//                 return;
//             }
//             if (map->mtx2[y][x] == 'N') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 1.5 * PI; //  3/2 𝜋  270°
//                 return;
//             }
//             if (map->mtx2[y][x] == 'E') 
//             {
//                 player->x = x + 0.5;
//                 player->y = y + 0.5;
//                 player->angle = 2 * PI; //  2 𝜋  360°
//                 return;
//             }
//         }
//     }
// }

// int	look_for_width(t_map map)
// {
// 	int	result;	
// 	map.x = 0;
// 	map.y = 0;
// 	result = 0;
// 	while (map.mtx2[map.x])
// 	{
// 		map.y = ft_strlen(map.mtx2[map.x]);
// 		if (map.y > result)
// 			result = map.y;
// 		map.x++;
// 	}
// 	map.x = 0;
// 	map.y = 0;
// 	return (result);
// }

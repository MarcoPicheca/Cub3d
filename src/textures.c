/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:14:35 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/26 19:37:24 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	toggle_door(t_game *game)
{
	double	newx;
	double	newy;
	int		tile_x;
	int		tile_y;
	char	cell;

	newx = game->player.x + cos(game->player.angle);
	newy = game->player.y + sin(game->player.angle);
	tile_x = (int)newx;
	tile_y = (int)newy;
	cell = game->map.mtx2[tile_y][tile_x];
	if (cell == '2')
		game->map.mtx2[tile_y][tile_x] = '3';
	else if (cell == '3')
	{
		if ((int)game->player.x == tile_x && (int)game->player.y == tile_y)
			return ;
		game->map.mtx2[tile_y][tile_x] = '2';
	}
}

void	free_gun_frames(t_game *game)
{
	int	i;

	i = 0;
	while (i <= 4)
	{
		if (game->player.gun_frames[i].img != NULL)
			mlx_destroy_image(game->mlx, game->player.gun_frames[i].img);
		i++;
	}
	free(game->player.gun_frames);
	game->player.gun_frames = NULL;
}

/*
sceglie quale texture applicare al muro colpito dal raggio.
se side_local e' zero vuol dire siamo sul muro verticale (2d)
se e' 1 abbiamo colpito un muro orizzontale.
verticale: se x e' positivo, stiamo guardando a destra(est), se negativo a 
sinistra(ovest) orizzontale: se y e' positivo, stiamo guardando verso
il basso, se negativo verso l'alto (si deve considerare il raggio partendo
dal giocatore come se fosse, quindi y (e x) negativo rispetto
alla posizione del giocatore, [tenere a mente che coordinate negative non
esistono in questo tipo di piano (minilibx/rendering grafico), quindi sono
negative rispetto al giocatore])
*/
t_tex	*pick_texture(t_game *game, t_3d_properties *prop, char tile)
{
	if (tile == '2')
		return (&game->door);
	if (prop->side_local == 0)
	{
		if (prop->ray_dir_x > 0)
			return (&game->tex_ea);
		else
			return (&game->tex_we);
	}
	else
	{
		if (prop->ray_dir_y > 0)
			return (&game->tex_so);
		else
			return (&game->tex_no);
	}
}

/*
calcola l'offset orizzontale di ogni pixel della texture per disegnare il muro.
se il muro e' verticale(orizzontalte), scaliamo il punto di 
collisione lungo y (lungo x) per block, per sapere
in quale punto della griglia siamo.
poi togliamo la parte intera con floorf, per sapere in quale punto del
blocco/muro siamo(valore tra 0 e 1) poi moltiplichiamo per width che e' la
larghezza originale del file xpm, moltiplichiamo * 4 per avere una resa
grafica adatta senza fare il resize a priori dell immagine originale
*/
int	compute_tex_x(t_tex *used_tex, t_3d_properties *prop)
{
	float	texture_offset;
	int		tex_x;

	texture_offset = 0.0f;
	if (prop->side_local == 0)
		texture_offset = prop->hit_y / (float)BLOCK;
	else
		texture_offset = prop->hit_x / (float)BLOCK;
	texture_offset = texture_offset - floorf(texture_offset);
	tex_x = (int)(texture_offset * (float)used_tex->width * 4);
	return (tex_x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:24:51 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/23 15:44:06 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

/*
imposta il numero di celle, il valore in pixel di ogni cella,
imposta l'offset orizzontale e verticale per la minimappa
*/
void	init_minimap_values(t_game *game)
{
	game->minimap.minimap_size = 14;
	game->minimap.cell_size = 11;
	game->minimap.offset_x = WIN_WIDTH - game->minimap.minimap_size
		* game->minimap.cell_size - 42;
	game->minimap.offset_y = 20;
}

/*
disegna la mappa attorno al giocatore, x e y servono per
aggiornare la minimappa avendo il giocatore come centro,
la moltiplicazione serve per convertire in coordinate pixel
*/
void	set_minimap_values(t_game *game,
		t_rectangle_params *values, int *x, int *y)
{
	values->start_x = game->minimap.offset_x
		+ (*x + game->minimap.minimap_size / 2) * game->minimap.cell_size;
	values->start_y = game->minimap.offset_y
		+ (*y + game->minimap.minimap_size / 2) * game->minimap.cell_size;
	values->width = game->minimap.cell_size;
	values->height = game->minimap.cell_size;
	values->color = game->minimap.minimap_colors;
}

/*
disegna un rettangolo per ogni cella della minimappa,
somma gli offset del giocatore e li casta a int perche siamo sulla griglia
controllo per non eccedere i limiti della mappa, se e' muro colore blu
se e' pavimento colore verde, se e' fuori mappa colore grigio
*/
void	draw_minimap_core(t_game *game, t_rectangle_params *rect, int x, int y)
{
	int	minimap_x;
	int	minimap_y;

	minimap_x = (int)game->player.x + x;
	minimap_y = (int)game->player.y + y;
	if (minimap_x >= 0 && minimap_x < game->map.width
		&& minimap_y >= 0 && minimap_y < game->map.height
		&& game->map.mtx2[minimap_y]
		&& minimap_x < ft_strlen(game->map.mtx2[minimap_y]))
	{
		if (minimap_x < ft_strlen(game->map.mtx2[minimap_y])
			&& game->map.mtx2[minimap_y][minimap_x]
			&& game->map.mtx2[minimap_y][minimap_x] == '1')
			game->minimap.minimap_colors = 0x0000FF;
		else
			game->minimap.minimap_colors = 0x55FF55;
	}
	else
		game->minimap.minimap_colors = 0XAAAAAA;
	set_minimap_values(game, rect, &x, &y);
	draw_rectangle(rect, game);
}

/*
disegna un rettangolo al centro della minimappa,
imposta il colore rosso per tale rettangolo e lo disegna
poi disegna un rettangolo interno leggermente piu piccolo
dello stesso colore del pavimento della minimappa
*/
void	draw_minimap_player(t_game *game)
{
	t_rectangle_params	rect;

	rect.start_x = game->minimap.offset_x
		+ (game->minimap.minimap_size / 2) * game->minimap.cell_size;
	rect.start_y = game->minimap.offset_y
		+ (game->minimap.minimap_size / 2) * game->minimap.cell_size;
	rect.color = 0xFF0000;
	rect.width = game->minimap.cell_size;
	rect.height = game->minimap.cell_size;
	draw_rectangle(&rect, game);
	rect.start_x += 2;
	rect.start_y += 2;
	rect.width -= 4;
	rect.height -= 4;
	rect.color = 0x55FF55;
	draw_rectangle(&rect, game);
}

/*
itera in una griglia centrata sul giocatore e 
disegna ogni rettangolo [cella] della minimappa
poi chiama draw_minimap_player per disegnare il giocatore
*/
void	draw_minimap(t_game *game)
{
	int					x;
	int					y;
	t_rectangle_params	rect;

	y = -game->minimap.minimap_size / 2;
	init_minimap_values(game);
	while (y <= game->minimap.minimap_size / 2)
	{
		x = -game->minimap.minimap_size / 2;
		while (x <= game->minimap.minimap_size / 2)
		{
			draw_minimap_core(game, &rect, x, y);
			x++;
		}
		y++;
	}
	draw_minimap_player(game);
}

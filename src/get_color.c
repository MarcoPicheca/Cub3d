/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschetti <tschetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 02:12:27 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/08 02:12:45 by tschetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
ottiene il colore di un pixel della texture in memoria
tx e ty sono le coordinate del pixel della texture
addr e' il puntatore alla texture in memoria
line_size e' la dimensione di una riga in byte
bpp e' il numero di bit per pixel.
solito calcolo per ottenere il pixel richiesto:
primo membro ty * line_size salta le righe,
secondo membro tx * byte salta le colonne
i 3 byte del pixel vengono assegnati a r,g,b.
ritorna i valori rgb in un unico intero
r << 16 sposta il valore di r di 16 bit a sinistra, nei bit 16-23
g << 8 di 8 bit a sinistra, nei bit 8-15
b rimane nei bit meno significativi 0-7
*/
int	get_tex_color(t_tex *tex, int tx, int ty)
{
	int		go_to;
	char	*dst;
	int		r;
	int		g;
	int		b;

	go_to = ty * tex->line_size + tx * (tex->bpp / 8);
	dst = tex->addr + go_to;
	b = (unsigned char)dst[0];
	g = (unsigned char)dst[1];
	r = (unsigned char)dst[2];
	return ((r << 16) | (g << 8) | (b));
}

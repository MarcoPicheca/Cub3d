/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall2_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:45:19 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/28 16:42:11 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
uso di mlx_xpm_file_to_image per caricare a schermo un xpm. 
game->mlx puntatore al server,
poi abbiamo il path del file, e infine larghezza e altezza
mlx_get_data_addr ottiene l indirizzo dei dati dell'immagine,
permettendo l'accesso a bpp, line_size e endian -> bit per pixel, 
byte per riga, ordine dei byte
*/
void	load_a_texture(t_game *game, t_tex *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		ft_putendl_fd("Error\nFailed to load texture", 2);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_size, &texture->endian);
}

void	add_path_and_call_mlx(t_game *game, int i)
{
	char	*path;
	char	*temp;

	temp = ft_itoa(5 + i);
	path = ft_strjoin("./textures/gun", temp);
	free(temp);
	temp = ft_strjoin(path, ".xpm");
	free(path);
	game->player.gun_frames[i].img = mlx_xpm_file_to_image(
			game->mlx, temp,
			&game->player.gun_frames[i].width,
			&game->player.gun_frames[i].height);
	free(temp);
	game->player.gun_frames[i].addr = mlx_get_data_addr(
			game->player.gun_frames[i].img,
			&game->player.gun_frames[i].bpp,
			&game->player.gun_frames[i].line_size,
			&game->player.gun_frames[i].endian);
}

void	calloc_and_control(t_game *game)
{
	game->player.gun_frames = ft_calloc(5, sizeof(t_tex));
	if (!game->player.gun_frames)
		exit_game(game);
}

void	load_gun_frames(t_game *game)
{
	int	i;

	i = 0;
	calloc_and_control(game);
	while (i <= 4)
	{
		add_path_and_call_mlx(game, i);
		if (!game->player.gun_frames[i].img)
		{
			write(2, "Error!\nFailed to load texture: \n", 33);
			exit_game(game);
		}
		i++;
	}
}

//carica le varie textures
void	load_textures(t_game *game)
{
	load_a_texture(game, &game->tex_no, game->map.path_no);
	load_a_texture(game, &game->tex_so, game->map.path_so);
	load_a_texture(game, &game->tex_we, game->map.path_we);
	load_a_texture(game, &game->tex_ea, game->map.path_ea);
	load_a_texture(game, &game->door, "textures/a.xpm");
	load_gun_frames(game);
}

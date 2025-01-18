/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:46:32 by tschetti          #+#    #+#             */
/*   Updated: 2025/01/18 17:31:06 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include "cub3d.h"

void	init_draw_crosshair_params(t_crosshair_params *params,
			int x_screen, int wall_top, int wall_bot);
void	draw_crosshair(t_game *game, t_crosshair_params *params);
void	draw_minimap(t_game *game);

#endif
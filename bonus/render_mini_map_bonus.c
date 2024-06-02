/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:11:14 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:41:15 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tile(t_cub3d *cub, int x, int y, float scale)
{
	if (cub->map.addr[y][x] == '1')
		draw_square(cub, (t_vec2){x * TILE_SIZE * scale, y * TILE_SIZE * scale},
			TILE_SIZE * scale, 0xFFFFFF80);
	else if (cub->map.addr[y][x] == 'V' || cub->map.addr[y][x] == 'H')
		draw_square(cub, (t_vec2){x * TILE_SIZE * scale, y * TILE_SIZE * scale},
			TILE_SIZE * scale, 0x0000FF80);
	else
		draw_square(cub, (t_vec2){x * TILE_SIZE * scale, y * TILE_SIZE * scale},
			TILE_SIZE * scale, 0x00000080);
}

void	draw_from_above(t_cub3d *cub, int map_width, int map_height,
		double scale)
{
	int	x;
	int	y;
	int	gap;

	y = 0;
	gap = 0;
	(void)gap;
	(void)scale;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			draw_tile(cub, x, y, scale);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cub3d *cub)
{
	double	scale;

	scale = cub->minimap_scale;
	draw_circle(cub, (t_vec2){cub->camera.pos.x * scale, cub->camera.pos.y
		* scale}, 4, 0xFF000080);
	ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * scale, cub->camera.pos.y
		* scale}, &(t_vec2){cub->camera.pos.x * scale + cos(cub->camera.dir)
		* 10, cub->camera.pos.y * scale + sin(cub->camera.dir) * 10},
		0xFF000080);
}

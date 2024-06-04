/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:11:14 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/03 18:42:14 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_cub3d *cub, float half_minimap_size)
{
	draw_circle(cub, (t_vec2){half_minimap_size, half_minimap_size}, 4,
		0xFF000080);
	ft_draw_line(cub, &(t_vec2){half_minimap_size, half_minimap_size},
		&(t_vec2){half_minimap_size + cos(cub->camera.dir) * 10,
		half_minimap_size + sin(cub->camera.dir) * 10}, 0xFF000080);
}

void	draw_tile(t_cub3d *cub, t_vec2 map_start, t_vec2 xy_screen)
{
	t_ivec2	xy_map;

	ft_pixel_put(cub->image, xy_screen.x, xy_screen.y, 0x00000080);
	xy_map.x = (int)(map_start.x / TILE_SIZE);
	xy_map.y = (int)(map_start.y / TILE_SIZE);
	if (xy_map.x >= 0 && xy_map.x < cub->map.width && xy_map.y >= 0
		&& xy_map.y < cub->map.height)
	{
		if (cub->map.addr[xy_map.y][xy_map.x] == '1')
			ft_pixel_put(cub->image, xy_screen.x, xy_screen.y, 0xFFFFFF80);
		else if (cub->map.addr[xy_map.y][xy_map.x] == 'V'
				|| cub->map.addr[xy_map.y][xy_map.x] == 'H')
			ft_pixel_put(cub->image, xy_screen.x, xy_screen.y, 0x0000FF80);
	}
}

void	draw_mini_map(t_cub3d *cub, float map_range)
{
	t_vec2	xy_screen;
	t_vec2	map_start;
	float	map_step;

	xy_screen.y = 0;
	map_start.y = cub->camera.pos.y - map_range;
	map_step = (TILE_SIZE * 20) / 200.0;
	while (xy_screen.y < 200)
	{
		xy_screen.x = 0;
		map_start.x = cub->camera.pos.x - map_range;
		while (xy_screen.x < 200)
		{
			draw_tile(cub, map_start, xy_screen);
			map_start.x += map_step;
			xy_screen.x++;
		}
		map_start.y += map_step;
		xy_screen.y++;
	}
	draw_player(cub, 100.0);
}

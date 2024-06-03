/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:11:14 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/03 01:50:01 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void draw_mini_map(t_cub3d *cub)
{
    int x_screen;
    int y_screen;
    int x_map;
    int y_map;
    float map_startx;
    float map_starty;
    
    y_screen = 0;
    
    float half_minimap_size = 100; // Half of the minimap size (200/2)
    float map_range = 10 * TILE_SIZE; // Range of tiles to display on one side
    
    map_starty = cub->camera.pos.y - map_range;
    float map_step = (TILE_SIZE * 20) / 200.0;
    
    while (y_screen < 200)
    {
        x_screen = 0;
        map_startx = cub->camera.pos.x - map_range;
        while (x_screen < 200)
        {
            ft_pixel_put(cub->image, x_screen, y_screen, 0x00000080);
            x_map = (int)(map_startx / TILE_SIZE);
            y_map = (int)(map_starty / TILE_SIZE);
            
            if (x_map >= 0 && x_map < cub->map.width && y_map >= 0 && y_map < cub->map.height)
            {
                if (cub->map.addr[y_map][x_map] == '1')
                    ft_pixel_put(cub->image, x_screen, y_screen, 0xFFFFFF80);
                else if (cub->map.addr[y_map][x_map] == 'V' || cub->map.addr[y_map][x_map] == 'H')
                    ft_pixel_put(cub->image, x_screen, y_screen, 0x0000FF80);                
            }
            map_startx += map_step;
            x_screen++;
        }
        map_starty += map_step;
        y_screen++;
    }
    // Render player at the center
    ft_pixel_put(cub->image, half_minimap_size, half_minimap_size, 0xFF000080);
}

void	draw_player(t_cub3d *cub)
{
	// double	scale;

	// scale = cub->minimap_scale;
	// draw_circle(cub, (t_vec2){100 , 100}, 4, 0xFF000080);
	// ft_draw_line(cub, &(t_vec2){100, 100}, &(t_vec2){100 + cos(cub->camera.dir)
	// 	* 10, 100 + sin(cub->camera.dir) * 10},
	// 	0xFF000080);
	(void)cub;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:25:35 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 23:29:00 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_bg(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_pixel_put(cub->image, x, y, cub->sky_color);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ft_pixel_put(cub->image, x, y, cub->floor_color);
			x++;
		}
		y++;
	}
}

void	pre_render(t_cub3d *cub)
{
	doors_update(cub);
	draw_bg(cub);
}

void	render_crosshair(t_cub3d *cub)
{
	int	x;
	int	y;

	x = WIDTH / 2 - 7;
	while (x < WIDTH / 2 + 7)
	{
		y = HEIGHT / 2 - 1;
		while (y < HEIGHT / 2 + 1)
		{
			ft_pixel_put(cub->image, x, y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
	y = HEIGHT / 2 - 7;
	while (y < HEIGHT / 2 + 7)
	{
		x = WIDTH / 2 - 1;
		while (x < WIDTH / 2 + 1)
		{
			ft_pixel_put(cub->image, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	render(t_cub3d *cub)
{
	t_cast_request	request;
	double			step;

	request.current_ray = 0;
	request.angle = cub->camera.dir - degree_to_radian(cub->camera.fov / 2);
	request.color = 0xFF0000FF;
	request.is_for_collision = false;
	step = degree_to_radian(cub->camera.fov) / WIDTH;
	while (request.current_ray < WIDTH)
	{
		ray_cast(cub, &cub->map, &request);
		request.angle += step;
		request.current_ray++;
	}
}

void	render_loop_handle(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	update_delta_time(cub);
	pre_render(cub);
	render(cub);
	render_crosshair(cub);
	update_gun(cub);
	render_gun(cub, NULL);
	//draw_from_above(cub, cub->map.width, cub->map.height, cub->minimap_scale);
	draw_mini_map(cub);
	draw_player(cub);
}

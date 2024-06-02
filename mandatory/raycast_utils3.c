/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:43:06 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:05:14 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	solve_door_texture(t_cub3d *cub, t_cast_result *res,
		t_wall_render_info *wr)
{
	float	x_factor;
	float	tex_x_off;
	float	close_factor;

	wr->texture = cub->door_texture;
	wr->tex_y_step = (float)wr->texture->height / wr->wall_height;
	close_factor = cub->door_infos[res->current_ray_door_index].close_factor;
	if (res->is_vertical)
	{
		x_factor = wr->hit_y - ((int)(wr->hit_y / TILE_SIZE) * TILE_SIZE);
		tex_x_off = wr->texture->width - wr->texture->width * close_factor;
		wr->tex_x = (wr->texture->width * x_factor) / TILE_SIZE;
		wr->tex_x -= tex_x_off;
	}
	else
	{
		x_factor = wr->hit_x - ((int)(wr->hit_x / TILE_SIZE) * TILE_SIZE);
		tex_x_off = wr->texture->width - wr->texture->width * close_factor;
		wr->tex_x = (wr->texture->width * x_factor) / TILE_SIZE;
		wr->tex_x += tex_x_off;
	}
}

void	render_door(t_cub3d *cub, t_cast_result *res, t_wall_render_info *wr)
{
	int	current_y;
	int	tex_color;

	if (!res->current_ray_is_door)
		return ;
	solve_door_texture(cub, res, wr);
	wr->tex_y_step = (float)wr->texture->height / wr->wall_height;
	wr->tex_y = 0;
	current_y = wr->wall_top;
	if (current_y < 0)
	{
		current_y = 0;
		wr->tex_y = abs((int)wr->wall_top) * wr->tex_y_step;
	}
	while (current_y < HEIGHT && current_y < wr->wall_top + wr->wall_height)
	{
		tex_color = get_color_texture(wr->texture, wr->tex_x, wr->tex_y);
		ft_pixel_put(cub->image, res->current_ray, current_y, tex_color);
		wr->tex_y += wr->tex_y_step;
		current_y++;
	}
}

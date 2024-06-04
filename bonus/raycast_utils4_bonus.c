/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils4_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:45:03 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/04 19:41:39 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	solve_v_texture(t_cub3d *cub, t_cast_result *res,
		t_wall_render_info *wr)
{
	float	normalizer;

	normalizer = wr->hit_y - (int)(wr->hit_y / TILE_SIZE) * TILE_SIZE;
	if (cos(res->angle) >= 0)
		wr->texture = cub->east_texture;
	else
	{
		wr->texture = cub->west_texture;
		normalizer = TILE_SIZE - normalizer;
	}
	wr->tex_x = normalizer * wr->texture->width / TILE_SIZE;
}

void	solve_h_texture(t_cub3d *cub, t_cast_result *res,
		t_wall_render_info *wr)
{
	float	normlizer;

	normlizer = wr->hit_x - (int)(wr->hit_x / TILE_SIZE) * TILE_SIZE;
	if (sin(res->angle) < 0)
		wr->texture = cub->north_texture;
	else
	{
		normlizer = TILE_SIZE - normlizer;
		wr->texture = cub->south_texture;
	}
	wr->tex_x = normlizer * wr->texture->width / TILE_SIZE;
}

void	build_wall_render_info(t_cub3d *cub, t_cast_result *res,
		t_wall_render_info *wr)
{
	float	correct_dist;
	float	distance_projection_plane;

	ft_bzero(wr, sizeof(t_wall_render_info));
	correct_dist = res->dist * cos(res->angle - cub->camera.dir);
	distance_projection_plane = (WIDTH / 2)
		/ tanf(degree_to_radian(cub->camera.fov / 2));
	wr->wall_height = (TILE_SIZE / correct_dist) * distance_projection_plane;
	wr->wall_top = (HEIGHT / 2) - ((int)wr->wall_height / 2);
	wr->hit_x = res->inter.x;
	wr->hit_y = res->inter.y;
}

void	render_wall(t_cub3d *cub, t_cast_result *res, t_wall_render_info *wr)
{
	int	current_y;
	int	tex_color;

	if (res->current_ray_is_door)
		return ;
	if (res->is_vertical)
		solve_v_texture(cub, res, wr);
	else
		solve_h_texture(cub, res, wr);
	wr->tex_y_step = (float)wr->texture->height / wr->wall_height;
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

void	render_execute(t_cub3d *cub, t_cast_result *res)
{
	t_wall_render_info	wr;

	build_wall_render_info(cub, res, &wr);
	render_wall(cub, res, &wr);
	render_door(cub, res, &wr);
}

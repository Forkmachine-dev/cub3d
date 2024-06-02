/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:27:52 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:28:18 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_cub3d *cub, t_vec2 pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_pixel_put(cub->image, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_ring(t_cub3d *cub, t_vec2 pos, int radius, int color)
{
	float	current_angle;
	float	cos_angle;
	float	sin_angle;
	t_vec2	point;
	float	angle_step;

	current_angle = 0;
	angle_step = 0.01;
	while (current_angle < 2 * M_PI)
	{
		cos_angle = cos(current_angle);
		sin_angle = sin(current_angle);
		point.x = pos.x + radius * cos_angle;
		point.y = pos.y + radius * sin_angle;
		ft_pixel_put(cub->image, point.x, point.y, color);
		current_angle += angle_step;
	}
}

void	draw_circle(t_cub3d *cub, t_vec2 pos, int radius, int color)
{
	int	current_radius;

	current_radius = 0;
	while (current_radius <= radius)
	{
		draw_ring(cub, pos, current_radius, color);
		current_radius++;
	}
}

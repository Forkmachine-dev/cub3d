/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:16:09 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:26:46 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	roatate_view(t_cub3d *cub)
{
	float	rot_speed;
	int		x;
	int		y;

	rot_speed = 0.07;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->camera.dir += rot_speed;
		if (cub->camera.dir > 2 * M_PI)
			cub->camera.dir -= 2 * M_PI;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->camera.dir -= rot_speed;
		if (cub->camera.dir < 0)
			cub->camera.dir += 2 * M_PI;
	}
	if (cub->mouse_locked)
	{
		mlx_get_mouse_pos(cub->mlx, &x, &y);
		mlx_set_mouse_pos(cub->mlx, cub->mlx->width / 2, cub->mlx->height / 2);
		cub->camera.dir += (cub->mlx->width / 2 - x) * (-0.01
				* cub->delta_time);
	}
}

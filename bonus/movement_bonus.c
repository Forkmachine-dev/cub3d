/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:12:39 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:35:53 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_movement(t_cub3d *cub, float *distances, t_vec2 *move)
{
	move->x = 0;
	move->y = 0;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) && distances[0] > 20)
	{
		move->x += cos(cub->camera.dir);
		move->y += sin(cub->camera.dir);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) && distances[1] > 20)
	{
		move->x += cos(cub->camera.dir + M_PI);
		move->y += sin(cub->camera.dir + M_PI);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A) && distances[2] > 20)
	{
		move->x += cos(cub->camera.dir - M_PI_2);
		move->y += sin(cub->camera.dir - M_PI_2);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) && distances[3] > 20)
	{
		move->x += cos(cub->camera.dir + M_PI_2);
		move->y += sin(cub->camera.dir + M_PI_2);
	}
}

void	normalize_movement(t_vec2 *move)
{
	float	length;

	if (move->x != 0 && move->y != 0)
	{
		length = sqrt(move->x * move->x + move->y * move->y);
		move->x /= length;
		move->y /= length;
	}
}

void	apply_movement(t_cub3d *cub, t_vec2 *move)
{
	float	move_speed;

	move_speed = 4;
	cub->camera.pos.x += move->x * move_speed;
	cub->camera.pos.y += move->y * move_speed;
}

void	movement(t_cub3d *cub)
{
	float	distances[4];
	t_vec2	move;

	solve_distances(cub, distances);
	calculate_movement(cub, distances, &move);
	normalize_movement(&move);
	apply_movement(cub, &move);
}

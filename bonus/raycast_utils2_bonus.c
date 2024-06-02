/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:41:37 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:03:24 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_direction	get_direction(double angle)
{
	t_direction	direction;

	ft_bzero(&direction, sizeof(t_direction));
	if (angle > 0 && angle < M_PI)
		direction.down = true;
	else
		direction.up = true;
	if (angle < M_PI_2 || angle > 3 * M_PI_2)
		direction.right = true;
	else
		direction.left = true;
	return (direction);
}

void	init_cast_result(t_cast_result *cast_result, t_cast_request *request)
{
	ft_bzero(cast_result, sizeof(t_cast_result));
	cast_result->angle = request->angle;
	cast_result->current_ray = request->current_ray;
	cast_result->is_for_collision = request->is_for_collision;
	cast_result->direction = get_direction(request->angle);
	cast_result->current_ray_is_door = false;
	cast_result->current_ray_door_index = -1;
}

void	normalize_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

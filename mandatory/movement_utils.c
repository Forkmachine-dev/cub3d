/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:35:39 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:36:32 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_close_factor(float *close_factor, t_cub3d *cub)
{
	*close_factor = cub->door_infos
	[cub->cast_result.current_ray_door_index]
		.close_factor;
}

void	solve_distances(t_cub3d *cub, float *distances)
{
	t_cast_request	request;
	float			close_factor;

	request.angle = cub->camera.dir;
	request.color = 0xFF0000FF;
	request.is_for_collision = true;
	distances[0] = ray_cast(cub, &cub->map, &request);
	update_close_factor(&close_factor, cub);
	if (cub->cast_result.current_ray_is_door && close_factor <= 0.21)
		distances[0] = 30;
	request.angle = cub->camera.dir + M_PI;
	distances[1] = ray_cast(cub, &cub->map, &request);
	update_close_factor(&close_factor, cub);
	if (cub->cast_result.current_ray_is_door && close_factor <= 0.21)
		distances[1] = 30;
	request.angle = cub->camera.dir - M_PI_2;
	distances[2] = ray_cast(cub, &cub->map, &request);
	update_close_factor(&close_factor, cub);
	if (cub->cast_result.current_ray_is_door && close_factor <= 0.21)
		distances[2] = 30;
	request.angle = cub->camera.dir + M_PI_2;
	distances[3] = ray_cast(cub, &cub->map, &request);
	update_close_factor(&close_factor, cub);
	if (cub->cast_result.current_ray_is_door && close_factor <= 0.21)
		distances[3] = 30;
}

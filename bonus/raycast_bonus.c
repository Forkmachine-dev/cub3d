/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:07:10 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:07:15 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cast_result	ray_cast_vertical(t_cub3d *cub, t_map *map,
		t_cast_request *request)
{
	t_cast_result	res;

	init_cast_result(&res, request);
	res.is_vertical = true;
	solve_v_intersections(cub, map, &res);
	res.dist = sqrt(pow(res.inter.x - cub->camera.pos.x, 2) + pow(res.inter.y
				- cub->camera.pos.y, 2));
	return (res);
}

t_cast_result	ray_cast_horizontal(t_cub3d *cub, t_map *map,
		t_cast_request *request)
{
	t_cast_result	res;

	init_cast_result(&res, request);
	res.is_vertical = false;
	solve_h_intersections(cub, map, &res);
	res.dist = sqrt(pow(res.inter.x - cub->camera.pos.x, 2) + pow(res.inter.y
				- cub->camera.pos.y, 2));
	return (res);
}

float	ray_cast(t_cub3d *cub, t_map *map, t_cast_request *request)
{
	t_cast_result	v_res;
	t_cast_result	h_res;
	t_cast_result	res;

	normalize_angle(&request->angle);
	v_res = ray_cast_vertical(cub, map, request);
	h_res = ray_cast_horizontal(cub, map, request);
	if (v_res.dist < h_res.dist)
		res = v_res;
	else
		res = h_res;
	cub->cast_result = res;
	render_execute(cub, &res);
	return (res.dist);
}

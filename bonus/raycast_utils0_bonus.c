/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:36:18 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 00:54:59 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	solve_h_intersections(t_cub3d *cub, t_map *map, t_cast_result *res)
{
	t_vec2	point;

	res->inter.y = floor(cub->camera.pos.y / TILE_SIZE) * TILE_SIZE;
	if (res->direction.down)
		res->inter.y += TILE_SIZE;
	res->inter.x = cub->camera.pos.x + (res->inter.y - cub->camera.pos.y)
		/ tan(res->angle);
	res->yo = TILE_SIZE;
	if (res->direction.up)
		res->yo *= -1;
	res->xo = TILE_SIZE / tan(res->angle);
	if ((res->direction.left && res->xo > 0) || (res->direction.right
			&& res->xo < 0))
		res->xo *= -1;
	while (true)
	{
		point.x = res->inter.x;
		point.y = res->inter.y;
		if (res->direction.up)
			point.y -= 1;
		if (is_solid_tile(point, map, cub, res))
			break ;
		res->inter.x += res->xo;
		res->inter.y += res->yo;
	}
}

void	solve_v_intersections(t_cub3d *cub, t_map *map, t_cast_result *res)
{
	t_vec2	point;

	res->inter.x = floor(cub->camera.pos.x / TILE_SIZE) * TILE_SIZE;
	if (res->direction.right)
		res->inter.x += TILE_SIZE;
	res->inter.y = cub->camera.pos.y + (res->inter.x - cub->camera.pos.x)
		* tan(res->angle);
	res->xo = TILE_SIZE;
	if (res->direction.left)
		res->xo *= -1;
	res->yo = TILE_SIZE * tan(res->angle);
	if ((res->direction.up && res->yo > 0) || (res->direction.down
			&& res->yo < 0))
		res->yo *= -1;
	while (true)
	{
		point.x = res->inter.x;
		point.y = res->inter.y;
		if (res->direction.left)
			point.x -= 1;
		if (is_solid_tile(point, map, cub, res))
			break ;
		res->inter.x += res->xo;
		res->inter.y += res->yo;
	}
}

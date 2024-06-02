/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:38:45 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:00:56 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tile_check(int *x_map, int *y_map, t_vec2 *point)
{
	*x_map = point->x / TILE_SIZE;
	*y_map = point->y / TILE_SIZE;
}

bool	intersect_door(t_cub3d *cub, t_cast_result *res, int i)
{
	t_vec2	p;
	t_vec2	factor;

	p.x = res->inter.x + (res->xo / 2);
	p.y = res->inter.y + (res->yo / 2);
	if (cub->door_infos[i].is_vertical)
	{
		factor.x = p.y - ((int)(p.y / TILE_SIZE) *TILE_SIZE);
		factor.x = (TILE_SIZE - factor.x) / TILE_SIZE;
		if (factor.x > cub->door_infos[i].close_factor)
			return (false);
		res->inter = p;
	}
	else
	{
		factor.y = p.x - ((int)(p.x / TILE_SIZE) *TILE_SIZE);
		factor.y = factor.y / TILE_SIZE;
		if (factor.y > cub->door_infos[i].close_factor)
			return (false);
		res->inter = p;
	}
	res->current_ray_is_door = true;
	res->current_ray_door_index = i;
	return (true);
}

bool	handle_door_checking(t_cub3d *cub, t_cast_result *res, int x_map,
		int y_map)
{
	int		i;
	t_map	*map;

	i = -1;
	map = &cub->map;
	if (!(map->addr[y_map][x_map] == 'V' || map->addr[y_map][x_map] == 'H'))
		return (false);
	while (++i < MAX_DOORS)
	{
		if (cub->door_infos[i].map_x == x_map
			&& cub->door_infos[i].map_y == y_map)
		{
			if ((res->is_vertical && !cub->door_infos[i].is_vertical)
				|| (!res->is_vertical && cub->door_infos[i].is_vertical))
				return (false);
			if (res->is_for_collision)
			{
				res->current_ray_is_door = true;
				res->current_ray_door_index = i;
				return (true);
			}
			return (intersect_door(cub, res, i));
		}
	}
	return (false);
}

bool	is_solid_tile(t_vec2 point, t_map *map, t_cub3d *cub,
		t_cast_result *res)
{
	int	x;
	int	y;

	init_tile_check(&x, &y, &point);
	if (x <= 0 || y <= 0 || x >= map->width - 1 || y >= map->height - 1)
		return (true);
	if (map->addr[y][x] == '1')
		return (true);
	return (handle_door_checking(cub, res, x, y));
}

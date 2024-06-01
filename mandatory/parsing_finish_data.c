/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_finish_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 20:44:15 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:45:40 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_door(t_cub3d *cub, int x, int y, int current_door)
{
	t_door_info	door_info;

	if (current_door >= MAX_DOORS)
	{
		printf("[ERROR]Max doors reached, Inocrrect map\n");
		return (EXIT_FAILURE);
	}
	door_info.map_x = x;
	door_info.map_y = y;
	door_info.close_factor = 1;
	door_info.is_opening = false;
	door_info.is_vertical = cub->map.addr[y][x] == 'V';
	cub->door_infos[current_door] = door_info;
	current_door++;
	return (EXIT_SUCCESS);
}

int	fill_door_data(t_cub3d *cub)
{
	int	x;
	int	y;
	int	current_door;

	current_door = 0;
	ft_bzero(cub->door_infos, sizeof(t_door_info) * MAX_DOORS);
	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			if (cub->map.addr[y][x] == 'V' || cub->map.addr[y][x] == 'H')
			{
				if (set_door(cub, x, y, current_door) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				current_door++;
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

static void	set_player(t_cub3d *cub, int x, int y, int degree)
{
	cub->camera.pos.x = x * TILE_SIZE + TILE_SIZE / 2;
	cub->camera.pos.y = y * TILE_SIZE + TILE_SIZE / 2;
	cub->camera.dir = degree_to_radian(degree);
}

int	find_player(t_cub3d *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			if (cub->map.addr[y][x] == 'N')
				set_player(cub, x, y, 270);
			else if (cub->map.addr[y][x] == 'S')
				set_player(cub, x, y, 90);
			else if (cub->map.addr[y][x] == 'E')
				set_player(cub, x, y, 0);
			else if (cub->map.addr[y][x] == 'W')
				set_player(cub, x, y, 180);
			if (cub->map.addr[y][x] == 'N' || cub->map.addr[y][x] == 'S'
				|| cub->map.addr[y][x] == 'E' || cub->map.addr[y][x] == 'W')
				return (EXIT_SUCCESS);
			x++;
		}
		y++;
	}
	return (EXIT_FAILURE);
}

int	determin_scale(t_cub3d *cub)
{
	double	initial_mini_map_scale;
	int		width_init;
	int		height_init;

	initial_mini_map_scale = 1;
	width_init = cub->map.width * TILE_SIZE
		* initial_mini_map_scale;
	height_init = cub->map.height * TILE_SIZE
		* initial_mini_map_scale;
	if (width_init > height_init)
		cub->minimap_scale = ((double)WIDTH / 5)
			/ width_init;
	else
		cub->minimap_scale = ((double)HEIGHT / 5)
			/ height_init;
	cub->minimap_scale = round(cub->minimap_scale * 16) / 16;
	printf("minimap scale %f\n", cub->minimap_scale);
	return (EXIT_SUCCESS);
}

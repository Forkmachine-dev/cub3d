/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:12:32 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:25:18 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_delta_time(t_cub3d *cub)
{
	double	current_time;

	current_time = mlx_get_time();
	cub->delta_time = current_time - cub->last_time;
	cub->last_time = current_time;
}

void	doors_update(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (i < MAX_DOORS)
	{
		if (cub->door_infos[i].map_x == -1)
			break ;
		if (cub->door_infos[i].is_opening)
		{
			cub->door_infos[i].close_factor -= 0.01;
			if (cub->door_infos[i].close_factor <= 0.2)
			{
				cub->door_infos[i].close_factor = 0.2;
			}
		}
		else
		{
			cub->door_infos[i].close_factor += 0.01;
			if (cub->door_infos[i].close_factor >= 1)
			{
				cub->door_infos[i].close_factor = 1;
			}
		}
		i++;
	}
}

void	update_gun(t_cub3d *cub)
{
	if (cub->gun_state.is_firing)
	{
		cub->gun_state.sprite_time += cub->delta_time;
		if (cub->gun_state.sprite_time > 0.05)
		{
			cub->gun_state.sprite_time = 0;
			cub->current_gun_index++;
			if (cub->current_gun_index >= 6)
			{
				cub->current_gun_index = 0;
				cub->gun_state.is_firing = false;
			}
		}
	}
}

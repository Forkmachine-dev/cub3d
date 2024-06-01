/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:39:32 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:21:51 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fire_mouse_hook(mouse_key_t button, action_t action,
		modifier_key_t mods, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		cub->gun_state.is_firing = true;
	}
}

void	open_door(mlx_key_data_t key, t_cub3d *cub)
{
	t_cast_request	req;
	float			dist;
	bool			*is_open;
	bool			is_door;

	req.angle = cub->camera.dir;
	req.color = 0x0000FFFF;
	req.current_ray = 0;
	req.is_for_collision = true;
	dist = ray_cast(cub, &cub->map, &req);
	is_open = &cub->door_infos
	[cub->cast_result.current_ray_door_index].is_opening;
	is_door = cub->cast_result.current_ray_is_door;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{
		if (is_door && dist < TILE_SIZE * 2)
		{
			if (*is_open)
				*is_open = false;
			else
				*is_open = true;
		}
	}
}

void	look_unlock_mouse(mlx_key_data_t key, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	if (key.key == MLX_KEY_F && key.action == MLX_PRESS)
	{
		if (cub->mouse_locked)
		{
			cub->mouse_locked = false;
			mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
		}
		else
		{
			cub->mouse_locked = true;
			mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
		}
		mlx_set_mouse_pos(cub->mlx, cub->mlx->width / 2, cub->mlx->height / 2);
	}
}

void	key_pess_hook(mlx_key_data_t key, void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	open_door(key, cub);
	look_unlock_mouse(key, cub);
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(cub->mlx);
}

void	ft_key_hooks(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	roatate_view(cub);
	movement(cub);
}

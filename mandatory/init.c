/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:14:26 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 22:46:07 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_window(t_cub3d *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!(cub->mlx))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!(cub->image))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_key_hook(cub->mlx, key_pess_hook, cub);
	mlx_loop_hook(cub->mlx, ft_key_hooks, cub);
	mlx_loop_hook(cub->mlx, render_loop_handle, cub);
	return (EXIT_SUCCESS);
}

int	load_textures(t_cub3d *cub)
{
	cub->north_texture = mlx_load_png(cub->no_texture_path);
	cub->south_texture = mlx_load_png(cub->so_texture_path);
	cub->west_texture = mlx_load_png(cub->we_texture_path);
	cub->east_texture = mlx_load_png(cub->ea_texture_path);
	cub->current_gun_index = 0;
	cub->gun_state.is_firing = false;
	cub->gun_state.sprite_time = 0;
	cub->last_time = mlx_get_time();
	return (EXIT_SUCCESS);
}

int	check_textures(t_cub3d *cub)
{
	int	i;

	i = 0;
	if (!cub->north_texture || !cub->south_texture || !cub->west_texture
		|| !cub->east_texture)
	{
		perr("can't load a wall texture");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_cub3d(t_cub3d *cub)
{
	if (open_window(cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	load_textures(cub);
	if (check_textures(cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cub->camera.fov = 60;
	cub->current_gun_index = 0;
	cub->gun_state.is_firing = false;
	cub->gun_state.sprite_time = 0;
	cub->last_time = mlx_get_time();
	return (EXIT_SUCCESS);
}

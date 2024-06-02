/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:08:45 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:53:36 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	all_textures_good(t_cub3d *cub)
{
	if (cub->parsing_checklist.invalid_key)
	{
		perr("Invalid map info key");
		return (0);
	}
	if (cub->no_texture_path && cub->so_texture_path && cub->we_texture_path
		&& cub->ea_texture_path && cub->gun0_texture_path
		&& cub->gun1_texture_path && cub->gun2_texture_path
		&& cub->gun3_texture_path && cub->gun4_texture_path
		&& cub->gun5_texture_path && cub->door_texture_path)
		return (1);
	perr("Missing textures");
	return (0);
}

int	check_textures_and_colors(t_cub3d *cub)
{
	if (cub->parsing_checklist.duplicated_components)
	{
		perr("Duplicated components");
		return (EXIT_FAILURE);
	}
	else if (cub->parsing_checklist.wrong_texture_ext)
	{
		perr("Wrong texture extension, Make sure the paths are correct[.png]");
		return (EXIT_FAILURE);
	}
	else if (!all_textures_good(cub))
		return (EXIT_FAILURE);
	else if (!cub->parsing_checklist.floor_color)
	{
		perr("Missing or invalid floor color\n");
		return (EXIT_FAILURE);
	}
	else if (!cub->parsing_checklist.sky_color)
	{
		perr("Missing or invalid ceiling color");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

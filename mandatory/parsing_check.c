/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:08:45 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 22:01:42 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"






static int all_textures_good(t_cub3d *cub)
{
    if (cub->no_texture_path && cub->so_texture_path 
        && cub->we_texture_path && cub->ea_texture_path
        && cub->gun0_texture_path && cub->gun1_texture_path
        && cub->gun2_texture_path && cub->gun3_texture_path
        && cub->gun4_texture_path && cub->gun5_texture_path
        && cub->door_texture_path)
        return (1);
    write(2, "[ERROR] Missing one or more texture paths\n", 43);
    return (0);
}

int check_textures_and_colors(t_cub3d *cub)
{
    if (cub->parsing_checklist.duplicated_components)
    {
        write(2, "[ERROR] Duplicated components\n", 31);
        return (EXIT_FAILURE);
    }
    else if (!all_textures_good(cub))
        return (EXIT_FAILURE);
    else if (cub->parsing_checklist.wrong_texture_ext)
    {
        write(2, "[ERROR] Wrong texture extension\n", 33);
        return (EXIT_FAILURE);
    }
    else if (!cub->parsing_checklist.floor_color)
    {
        write(2, "[ERROR] Missing floor color\n", 29);
        return (EXIT_FAILURE);
    }
    else if (!cub->parsing_checklist.sky_color)
    {
        write(2, "[ERROR] Missing color\n", 23);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

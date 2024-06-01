/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:43:01 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 22:56:26 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_textures_paths(t_cub3d *cub)
{
    free(cub->no_texture_path);
    free(cub->so_texture_path);
    free(cub->we_texture_path);
    free(cub->ea_texture_path);
    free(cub->door_texture_path);
    free(cub->gun0_texture_path);
    free(cub->gun1_texture_path);
    free(cub->gun2_texture_path);
    free(cub->gun3_texture_path);
    free(cub->gun4_texture_path);
    free(cub->gun5_texture_path);
    cub->no_texture_path = NULL;
    cub->so_texture_path = NULL;
    cub->we_texture_path = NULL;
    cub->ea_texture_path = NULL;
    cub->door_texture_path = NULL;
    cub->gun0_texture_path = NULL;
    cub->gun1_texture_path = NULL;
    cub->gun2_texture_path = NULL;
    cub->gun3_texture_path = NULL;
    cub->gun4_texture_path = NULL;
    cub->gun5_texture_path = NULL;
}

static void free_map(t_cub3d *cub)
{
    int i;

    i = 0;
    while (i < cub->map.height)
    {
        free(cub->map.addr[i]);
        cub->map.addr[i] = NULL;
        i++;
    }
    free(cub->map.addr);
    cub->map.addr = NULL;
}

static void ft_free_image(mlx_texture_t **txt)
{
    if (*txt)
    {
        mlx_delete_texture((*txt));
        *txt = NULL;
    }
}
static void free_mlx_images(t_cub3d *cub)
{
    int i;
    ft_free_image(&cub->north_texture);
    ft_free_image(&cub->south_texture);
    ft_free_image(&cub->west_texture);
    ft_free_image(&cub->east_texture);
    ft_free_image(&cub->door_texture);

    i = 0;
    while (i < 6)
    {
        ft_free_image(&cub->gun_textures[i]);
        i++;
    }
}

void free_cub(t_cub3d *cub)
{
    free_textures_paths(cub);
    free_mlx_images(cub);
    free_map(cub);
}


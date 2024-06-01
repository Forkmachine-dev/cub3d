/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:05:57 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 22:53:53 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int solve_texture(char *name, char **path, char *line, t_cub3d *cub)
{
    int len;

    len = ft_strlen(name);
    if (ft_strncmp(line, name, len) == 0)
    {
        if(dup_checklist(&cub->duplication_checklist, name))
        {
            cub->parsing_checklist.duplicated_components = true;
            return (1);
        }
        get_image_path(cub, path, line + len);
        return (1);
    }
    return (0);
}

static void solve_wall_textures(t_cub3d* cub, char *line, int i, int *solved)
{
    *solved += solve_texture("NO", &cub->no_texture_path, line + i, cub);
    *solved += solve_texture("SO", &cub->so_texture_path, line + i, cub);
    *solved += solve_texture("WE", &cub->we_texture_path, line + i, cub);
    *solved += solve_texture("EA", &cub->ea_texture_path, line + i, cub);
}
static void solve_door_texture(t_cub3d* cub, char *line, int i, int *solved)
{
   *solved +=  solve_texture("DO", &cub->door_texture_path, line + i, cub);
}

static void solve_gun_textures(t_cub3d* cub, char *line, int i, int *solved)
{
    *solved +=  solve_texture("GU0", &cub->gun0_texture_path, line + i, cub);
    *solved += solve_texture("GU1", &cub->gun1_texture_path, line + i, cub);
    *solved += solve_texture("GU2", &cub->gun2_texture_path, line + i, cub);
    *solved += solve_texture("GU3", &cub->gun3_texture_path, line + i, cub);
    *solved += solve_texture("GU4", &cub->gun4_texture_path, line + i, cub);
    *solved +=  solve_texture("GU5", &cub->gun5_texture_path, line + i, cub);
}



int parse_info_part(t_cub3d *cub, int fd)
{
    char *line;
    int solved = 0;
    int i;

    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        i = skip_spaces(&line);
        solve_wall_textures(cub, line, i, &solved);
        solve_door_texture(cub, line, i, &solved);
        solve_gun_textures(cub, line, i, &solved);
        solve_colors(cub, line, i, &solved);
        free(line);
        if (solved == 13)
            break;
        line = get_next_line(fd);
    }
    if(!line)
        get_next_line(fd);
    free_duplication_checklist(cub->duplication_checklist);
    cub->duplication_checklist = NULL;
    return (check_textures_and_colors(cub));
}

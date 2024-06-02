/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_info_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:58:52 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:59:45 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	solve_texture(char *name, char **path, char *line, t_cub3d *cub)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strncmp(line, name, len) == 0)
	{
		if (dup_checklist(&cub->duplication_checklist, name))
		{
			cub->parsing_checklist.duplicated_components = true;
			return (1);
		}
		get_image_path(cub, path, line + len);
		return (1);
	}
	return (0);
}

static void	solve_wall_textures(t_cub3d *cub, char *line, int i, int *solved)
{
	*solved += solve_texture("NO ", &cub->no_texture_path, line + i, cub);
	*solved += solve_texture("SO ", &cub->so_texture_path, line + i, cub);
	*solved += solve_texture("WE ", &cub->we_texture_path, line + i, cub);
	*solved += solve_texture("EA ", &cub->ea_texture_path, line + i, cub);
}

static void	solve_door_texture(t_cub3d *cub, char *line, int i, int *solved)
{
	*solved += solve_texture("DO ", &cub->door_texture_path, line + i, cub);
}

static void	solve_gun_textures(t_cub3d *cub, char *line, int i, int *solved)
{
	*solved += solve_texture("GU0 ", &cub->gun0_texture_path, line + i, cub);
	*solved += solve_texture("GU1 ", &cub->gun1_texture_path, line + i, cub);
	*solved += solve_texture("GU2 ", &cub->gun2_texture_path, line + i, cub);
	*solved += solve_texture("GU3 ", &cub->gun3_texture_path, line + i, cub);
	*solved += solve_texture("GU4 ", &cub->gun4_texture_path, line + i, cub);
	*solved += solve_texture("GU5 ", &cub->gun5_texture_path, line + i, cub);
}

bool	evaluate_key(t_cub3d *cub, char *line, int i, int *solved)
{
	if (ft_strncmp("NO ", line + i, 3) == 0
		|| ft_strncmp("SO ", line + i, 3) == 0
		|| ft_strncmp("WE ", line + i, 3) == 0
		|| ft_strncmp("EA ", line + i, 3) == 0
		|| ft_strncmp("DO ", line + i, 3) == 0
		|| ft_strncmp("GU0 ", line + i, 4) == 0
		|| ft_strncmp("GU1 ", line + i, 4) == 0
		|| ft_strncmp("GU2 ", line + i, 4) == 0
		|| ft_strncmp("GU3 ", line + i, 4) == 0
		|| ft_strncmp("GU4 ", line + i, 4) == 0
		|| ft_strncmp("GU5 ", line + i, 4) == 0
		|| ft_strncmp("F ", line + i, 2) == 0
		|| ft_strncmp("C ", line + i, 2) == 0)
	{
		solve_wall_textures(cub, line, i, solved);
		solve_door_texture(cub, line, i, solved);
		solve_gun_textures(cub, line, i, solved);
		solve_colors(cub, line, i, solved);
		return (true);
	}
	else if (line[i] == '\0' || line[i] == '\n')
		return (true);
	cub->parsing_checklist.invalid_key = true;
	return (false);
}

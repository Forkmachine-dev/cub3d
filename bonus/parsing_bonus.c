/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:15:12 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 23:08:50 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_parse_result_debug(t_cub3d *cub)
{
	int	i;

	printf("Map height: %d\n", cub->map.height);
	printf("Map width: %d\n", cub->map.width);
	i = -1;
	while (++i < cub->map.height)
		printf("[%s]\n", cub->map.addr[i]);
	printf("NO: %s\n", cub->no_texture_path);
	printf("SO: %s\n", cub->so_texture_path);
	printf("WE: %s\n", cub->we_texture_path);
	printf("EA: %s\n", cub->ea_texture_path);
	printf("DO: %s\n", cub->door_texture_path);
	printf("GU0: %s\n", cub->gun0_texture_path);
	printf("GU1: %s\n", cub->gun1_texture_path);
	printf("GU2: %s\n", cub->gun2_texture_path);
	printf("GU3: %s\n", cub->gun3_texture_path);
	printf("GU4: %s\n", cub->gun4_texture_path);
	printf("GU5: %s\n", cub->gun5_texture_path);
	printf("F: %d, in rpg r: %d, in g: %d, in b: %d\n", cub->floor_color,
		(cub->floor_color >> 16) & 0xFF, (cub->floor_color >> 8) & 0xFF,
		cub->floor_color & 0xFF);
	printf("C: %d, in rpg r: %d, in g: %d, in b: %d\n", cub->sky_color,
		(cub->sky_color >> 16) & 0xFF, (cub->sky_color >> 8) & 0xFF,
		cub->sky_color & 0xFF);
}

int	check_file_ext(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
	{
		perr("Wrong file extension, Make sure the file is a [.cub] file");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	finish_filling_data(t_cub3d *cub)
{
	int	err_scale;
	int	err_door;
	int	err_player;

	err_scale = determin_scale(cub);
	err_door = fill_door_data(cub);
	err_player = find_player(cub);
	if (err_scale == EXIT_FAILURE || err_door == EXIT_FAILURE
		|| err_player == EXIT_FAILURE)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parse_map(t_cub3d *cub, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		perr("Wrong number of arguments, Make sure to provide a [.cub] file");
		return (EXIT_FAILURE);
	}
	if (check_file_ext(argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perr("Can't open the file");
		return (EXIT_FAILURE);
	}
	if (parse_info_part(cub, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parse_map_part(cub, fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(fd);
	if (finish_filling_data(cub) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

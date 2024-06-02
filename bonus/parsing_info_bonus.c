/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:05:57 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:59:31 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_info_part(t_cub3d *cub, int fd)
{
	char	*line;
	int		solved;
	int		i;

	solved = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = skip_spaces(&line);
		if (!evaluate_key(cub, line, i, &solved))
		{
			free(line);
			break ;
		}
		free(line);
		if (solved == 13)
			break ;
		line = get_next_line(fd);
	}
	if (!line)
		get_next_line(fd);
	free_duplication_checklist(cub->duplication_checklist);
	cub->duplication_checklist = NULL;
	return (check_textures_and_colors(cub));
}

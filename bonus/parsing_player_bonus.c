/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:58:45 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:07:46 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_cell_valid(t_map_row *map_row, int i)
{
	return (up_valid(map_row->up_row, i) && down_valid(map_row->down_row, i)
		&& !is_space(map_row->row[i + 1]) && (i > 0 
			&& !is_space(map_row->row[i - 1])));
}

int	is_player_valid(t_map_row *map_row)
{
	t_map_row	*crow;
	int			player_count;
	int			i;

	player_count = 0;
	crow = map_row;
	while (crow)
	{
		i = -1;
		while (crow->row[++i])
		{
			if (crow->row[i] == 'N' || crow->row[i] == 'S'
				|| crow->row[i] == 'E' || crow->row[i] == 'W')
			{
				player_count++;
				if (player_count > 1 || !is_player_cell_valid(crow, i))
					return (perr("Invalid player cell"));
			}
		}
		crow = crow->down_row;
	}
	if (player_count == 0)
		return (perr("No player found"));
	return (is_door_valid(map_row));
}

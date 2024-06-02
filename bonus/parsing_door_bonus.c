/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:55:38 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:08:35 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	up_row_cmp(t_map_row *up, int at, char c)
{
	if (up == NULL)
		return (0);
	if (up->size <= at)
		return (0);
	if (up->row[at] == c)
		return (1);
	return (0);
}

static int	down_row_cmp(t_map_row *down, int at, char c)
{
	if (down == NULL)
		return (0);
	if (down->size <= at)
		return (0);
	if (down->row[at] == c)
		return (1);
	return (0);
}

static int	is_door_cell_valid(t_map_row *map_row, int i)
{
	if (map_row->row[i] == 'V' && !(up_row_cmp(map_row->up_row, i, '1')
			&& down_row_cmp(map_row->down_row, i, '1')))
		return (0);
	if (map_row->row[i] == 'H' && !(map_row->row[i + 1] == '1' && i > 0
			&& map_row->row[i - 1] == '1'))
		return (0);
	return (1);
}

int	is_door_valid(t_map_row *map_row)
{
	t_map_row	*crow;
	int			i;

	crow = map_row;
	while (crow)
	{
		i = 0;
		while (crow->row[i])
		{
			if (crow->row[i] == 'V' || crow->row[i] == 'H')
			{
				if (!is_door_cell_valid(crow, i))
				{
					perr("Invalid door cell");
					return (EXIT_FAILURE);
				}
			}
			i++;
		}
		crow = crow->down_row;
	}
	return (EXIT_SUCCESS);
}

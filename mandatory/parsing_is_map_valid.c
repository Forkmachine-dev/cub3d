/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:05:17 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 19:38:38 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int check_conds(t_map_row *crow, int i)
{
    t_map_row *up;
    t_map_row *down;
    
    up = crow->up_row;
    down = crow->down_row;
    if(!is_valid_char(crow->row[i]))
        return (EXIT_FAILURE);
    if(crow->row[i] == '1')
        return (EXIT_SUCCESS);
    if((!one_or_space(crow->row[i]) && crow->row[i + 1] == '\0')
        || (!one_or_space(crow->row[i]) && is_space(crow->row[i + 1]))
        || (is_space(crow->row[i]) && !one_or_space(crow->row[i + 1]))
        || (!one_or_space(crow->row[i]) && !up_valid(up, i))
        || (!one_or_space(crow->row[i]) && !down_valid(down, i)))
        {
            write(2, "[ERROR] Invalid map\n", 21);
            return (EXIT_FAILURE);
        }
    return (EXIT_SUCCESS);
}

int is_map_valid(t_map_row *map_row)
{
    t_map_row *crow;
    int i;
    
    crow = map_row;
    while (crow)
    {
        i = 0;
        i = skip_spaces(&crow->row);
        if(crow->row[i] != '1')
            return (EXIT_FAILURE);
        while (crow->row[i])
        {
            if(check_conds(crow, i) == EXIT_FAILURE)
                return (EXIT_FAILURE);
            i++;
        }
        crow = crow->down_row;
    }
    return (is_player_valid(map_row));
}




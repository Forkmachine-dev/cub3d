/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:33:12 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 19:36:58 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map_rows(t_map_row *map_row)
{
    t_map_row *tmp;

    while (map_row)
    {
        tmp = map_row;
        map_row = map_row->down_row;
        free(tmp->row);
        free(tmp);
    }
}

void add_map_row(t_map_row **map_row, char *line)
{
    t_map_row *new_row;
    t_map_row *tmp;

    new_row = malloc(sizeof(t_map_row));
    new_row->row = line;
    new_row->size = ft_strlen(line);
    new_row->up_row = NULL;
    new_row->down_row = NULL;
    if (*map_row == NULL)
    {
        *map_row = new_row;
        return;
    }
    tmp = *map_row;
    while (tmp->down_row)
        tmp = tmp->down_row;
    tmp->down_row = new_row;
    new_row->up_row = tmp;
}

static int put_rows(t_cub3d *cub, t_map_row *map_row, int max_row_size, int row_count)
{
    int row_index;
    t_map_row *crow;

    row_index = 0;
    crow = map_row;
    cub->map.height = row_count;
    cub->map.width = max_row_size;
    cub->map.addr = malloc(sizeof(char *) * row_count);
    if (!cub->map.addr)
        return (EXIT_FAILURE);
    while (crow)
    {
        cub->map.addr[row_index] = (char *)malloc(sizeof(char) * (max_row_size + 1));
        if (!cub->map.addr[row_index])
            return (EXIT_FAILURE);
        ft_memset(cub->map.addr[row_index], ' ', max_row_size);
        cub->map.addr[row_index][max_row_size] = '\0';
        ft_memcpy(cub->map.addr[row_index], crow->row, crow->size);
        row_index++;
        crow = crow->down_row;
    }
    return (EXIT_SUCCESS);
}

static int fill_cub_map(t_cub3d *cub, t_map_row *map_row)
{
    (void)cub;
    (void)map_row;
    int max_row_size;
    int row_count;
    t_map_row *crow;

    max_row_size = 0;
    row_count = 0;
    crow = map_row;
    while (crow)
    {
        if (crow->size > max_row_size)
            max_row_size = crow->size;
        row_count++;
        crow = crow->down_row;
    }
    return (put_rows(cub, map_row, max_row_size, row_count));
}

int parse_map_part(t_cub3d *cub,  int fd)
{
    char *line;
    t_map_row *map_row;

    line = skip_empty_lines(fd);
    map_row = NULL;
    while(line)
    {
        put_terminator_at_newline(line);
        add_map_row(&map_row, line);
        line = get_next_line(fd);
    }
    get_next_line(fd);
    if(is_map_valid(map_row) == EXIT_FAILURE)
    {
        free_map_rows(map_row);
        return (EXIT_FAILURE);
    }
    if(fill_cub_map(cub, map_row) == EXIT_FAILURE)
    {
        free_map_rows(map_row);
        return (EXIT_FAILURE);
    }
    free_map_rows(map_row);
    return (EXIT_SUCCESS);
}
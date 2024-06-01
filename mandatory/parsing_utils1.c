/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:54:44 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 19:30:55 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int skip_spaces(char **line)
{
    int i;

    i = 0;
    while ((*line)[i] == ' ' || (*line)[i] == '\t')
        i++;
    return (i);
}

int up_valid(t_map_row *up, int at)
{
    if (up == NULL)
        return (0);
    if (up->size <= at)
        return (0);
    if (up->row[at] == ' ')
        return (0);
    return (1);
}

int down_valid(t_map_row *down, int at)
{
    if (down == NULL)
        return (0);
    if (down->size <= at)
        return (0);
    if (down->row[at] == ' ')
        return (0);
    return (1);
}

void put_terminator_at_newline(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            return;
        }
        i++;
    }
}

char* skip_empty_lines(int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line && *line == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}


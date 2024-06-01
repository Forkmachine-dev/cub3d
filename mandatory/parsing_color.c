/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 19:01:14 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 22:10:06 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_all_digit(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (!ft_isdigit(line[i]) && !is_space(line[i]))
            return (0);
        i++;
    }
    return (1);
}
void free_values(char **values)
{
    int i;

    i = 0;
    while (values[i])
    {
        free(values[i]);
        i++;
    }
    free(values);
}

static int parse_color(char *line, int *out_color)
{
    int r;
    int g;
    int b;
    
    put_terminator_at_newline(line);
    while(is_space(*line))
        line++;
    char **values = ft_split(line, ',');
    if(!values || !values[0] || !values[1] || !values[2] || values[3]
    || !is_all_digit(values[0]) || !is_all_digit(values[1]) || !is_all_digit(values[2]))
    {
        free_values(values);
        return (0);
    }
    r = ft_atoi(values[0]);
    g = ft_atoi(values[1]);
    b = ft_atoi(values[2]);
    free_values(values);
    *out_color = (255 << 24) | (r << 16) | (g << 8) | b;
    return (1);
}
void solve_colors(t_cub3d* cub, char *line, int i, int *solved)
{
    if (ft_strncmp(line + i, "F", 1) == 0)
    {
        if(dup_checklist(&cub->duplication_checklist, "F"))
            cub->parsing_checklist.duplicated_components = true;
        if(parse_color(line + i + 1, &cub->floor_color))
            cub->parsing_checklist.floor_color = true;
        (*solved)++;
    }
    else if (ft_strncmp(line + i, "C", 1) == 0)
    {
        if(dup_checklist(&cub->duplication_checklist, "C"))
            cub->parsing_checklist.duplicated_components = true;
        if(parse_color(line + i + 1, &cub->sky_color))
            cub->parsing_checklist.sky_color = true;
        (*solved)++;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:15:12 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 02:44:56 by mel-akhd         ###   ########.fr       */
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

int is_space(char c)
{
    return (c == ' ' || c == '\t');
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

int up_row_cmp(t_map_row *up, int at, char c)
{
    if (up == NULL)
        return (0);
    if (up->size <= at)
        return (0);
    if (up->row[at] == c)
        return (1);
    return (0);
}
int down_row_cmp(t_map_row *down, int at, char c)
{
    if (down == NULL)
        return (0);
    if (down->size <= at)
        return (0);
    if (down->row[at] == c)
        return (1);
    return (0);
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

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'V' || c == 'H' || is_space(c));
}

int check_conds(t_map_row *crow, int i, int *line_is_closed)
{
    t_map_row *up;
    t_map_row *down;
    
    up = crow->up_row;
    down = crow->down_row;
    if(!is_valid_char(crow->row[i]))
        return (EXIT_FAILURE);
    if(crow->row[i] == '1')
    {
        *line_is_closed = 1;
        return (EXIT_SUCCESS);
    }
    if((i == crow->size && *line_is_closed == 0)
        || (crow->row[i] == '0' && is_space(crow->row[i + 1]))
        || (is_space(crow->row[i]) && crow->row[i + 1] == '0')
        || (crow->row[i] == '0' && !up_valid(up, i))
        || (crow->row[i] == '0' && !down_valid(down, i)))
        {
            write(2, "[ERROR] Invalid map\n", 21);
            return (EXIT_FAILURE);
        }
    line_is_closed = 0;
    return (EXIT_SUCCESS);
}

int is_player_cell_valid(t_map_row *map_row, int i)
{
    return (up_valid(map_row->up_row, i) && down_valid(map_row->down_row, i)
         && !is_space(map_row->row[i + 1]) && (i > 0 && !is_space(map_row->row[i - 1])));
}

int is_door_cell_valid(t_map_row *map_row, int i)
{
    if(map_row->row[i] == 'V' && !(up_row_cmp(map_row->up_row, i, '1')
        && down_row_cmp(map_row->down_row, i, '1')))
        return (0);
    if(map_row->row[i] == 'H' && !(map_row->row[i + 1] == '1' && i > 0 && map_row->row[i - 1] == '1'))
        return (0);
    return (1);
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

int fill_cub_map(t_cub3d *cub, t_map_row *map_row)
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

int is_door_valid(t_map_row *map_row)
{
    t_map_row *crow;
    int i;
    
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
                    write(2, "[ERROR] Invalid door cell\n", 27);
                    return (EXIT_FAILURE);
                }
            }
            i++;
        }
        crow = crow->down_row;
    }
    return (EXIT_SUCCESS);
}

int is_player_valid(t_map_row *map_row)
{
    t_map_row *crow;
    int player_count;
    int i;
    
    player_count = 0;
    crow = map_row;
    while (crow)
    {
        i = 0;
        while (crow->row[i])
        {
            if (crow->row[i] == 'N' || crow->row[i] == 'S' 
                || crow->row[i] == 'E' || crow->row[i] == 'W')
            {
                player_count++;
                if (player_count > 1 || !is_player_cell_valid(crow, i))
                    return (write(2, "[ERROR] Invalid player cell\n", 29), EXIT_FAILURE);
            }
            i++;
        }
        crow = crow->down_row;
    }
    return (is_door_valid(map_row));
}

int is_map_valid(t_map_row *map_row)
{
    t_map_row *crow;
    int i;
    int line_is_closed;
    
    crow = map_row;
    while (crow)
    {
        i = 0;
        line_is_closed = 0;
        i = skip_spaces(&crow->row);
    
        if(crow->row[i] != '1')
            return (EXIT_FAILURE);
        while (crow->row[i])
        {
            if(check_conds(crow, i, &line_is_closed) == EXIT_FAILURE)
                return (EXIT_FAILURE);
            i++;
        }
        crow = crow->down_row;
    }
    return (is_player_valid(map_row));
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

int get_image_path(t_cub3d *cub, char **dist ,char *line)
{
    int i;
    int to_copy;

    i = 0;
    to_copy = 0;
    if(!line || !line[i])
        return (0);
  
    i = skip_spaces(&line);
    if(line[i] == '\0')
        return (0);
    while(line[i + to_copy] && line[i + to_copy] !='\n')
        to_copy++;
    *dist = ft_substr(line, i, to_copy);
    if(!*dist)
        return (0);
    int len = ft_strlen(*dist);
    if (len < 4 || ft_strncmp(*dist + len - 4, ".png", 4) != 0)
    {
        free(*dist);
        cub->parsing_checklist.wrong_texture_ext = true;
        return (0);
    }
    return (1);
}

int is_all_digit(char *line)
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

int parse_color(char *line, int *out_color)
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
        return (0);
    r = ft_atoi(values[0]);
    g = ft_atoi(values[1]);
    b = ft_atoi(values[2]);
    *out_color = (255 << 24) | (r << 16) | (g << 8) | b;
    return (1);
}

void add_to_dup_checklist(t_duplication_checklist **list, char *component)
{
    t_duplication_checklist *new_node;
    t_duplication_checklist *tmp;

    new_node = malloc(sizeof(t_duplication_checklist));
    new_node->component = component;
    new_node->next = NULL;
    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    tmp = *list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

int dup_checklist(t_duplication_checklist **list, char *component)
{
    t_duplication_checklist *tmp;
    int len;

    len = ft_strlen(component);
    tmp = *list;
    while (tmp)
    {
        if (ft_strncmp(tmp->component, component, len + 1) == 0)
            return (1);
        tmp = tmp->next;
    }
    add_to_dup_checklist(list, component);
    return (0);
}

int solve_texture(char *name, char **path, char *line, t_cub3d *cub)
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

void solve_gun_textures(t_cub3d* cub, char *line, int i, int *solved)
{
    *solved +=  solve_texture("GU0", &cub->gun0_texture_path, line + i, cub);
    *solved += solve_texture("GU1", &cub->gun1_texture_path, line + i, cub);
    *solved += solve_texture("GU2", &cub->gun2_texture_path, line + i, cub);
    *solved += solve_texture("GU3", &cub->gun3_texture_path, line + i, cub);
    *solved += solve_texture("GU4", &cub->gun4_texture_path, line + i, cub);
    *solved +=  solve_texture("GU5", &cub->gun5_texture_path, line + i, cub);
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

int all_textures_good(t_cub3d *cub)
{
    if (cub->no_texture_path && cub->so_texture_path 
        && cub->we_texture_path && cub->ea_texture_path
        && cub->gun0_texture_path && cub->gun1_texture_path
        && cub->gun2_texture_path && cub->gun3_texture_path
        && cub->gun4_texture_path && cub->gun5_texture_path
        && cub->door_texture_path)
        return (1);
    write(2, "[ERROR] Missing one or more texture paths\n", 43);
    return (0);
}

int check_textures_and_colors(t_cub3d *cub)
{
    if (cub->parsing_checklist.duplicated_components)
    {
        write(2, "[ERROR] Duplicated components\n", 31);
        return (EXIT_FAILURE);
    }
    else if (!all_textures_good(cub))
        return (EXIT_FAILURE);
    else if (cub->parsing_checklist.wrong_texture_ext)
    {
        write(2, "[ERROR] Wrong texture extension\n", 33);
        return (EXIT_FAILURE);
    }
    else if (!cub->parsing_checklist.floor_color)
    {
        write(2, "[ERROR] Missing floor color\n", 29);
        return (EXIT_FAILURE);
    }
    else if (!cub->parsing_checklist.sky_color)
    {
        write(2, "[ERROR] Missing color\n", 23);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
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
        if (solved == 13)
            break;
        free(line);
        line = get_next_line(fd);
    }
    return (check_textures_and_colors(cub));
}

void print_parse_result_debug(t_cub3d *cub)
{
    printf("Map height: %d\n", cub->map.height);
    printf("Map width: %d\n", cub->map.width);
    int i = 0;
    while (i < cub->map.height)
    {
        printf("[%s]\n", cub->map.addr[i]);
        i++;
    }
    printf("NO: %s\n", cub->no_texture_path);
    printf("SO: %s\n", cub->so_texture_path);
    printf("WE: %s\n", cub->we_texture_path);
    printf("EA: %s\n", cub->ea_texture_path);
    printf("GU0: %s\n", cub->gun0_texture_path);
    printf("GU1: %s\n", cub->gun1_texture_path);
    printf("GU2: %s\n", cub->gun2_texture_path);
    printf("GU3: %s\n", cub->gun3_texture_path);
    printf("GU4: %s\n", cub->gun4_texture_path);
    printf("GU5: %s\n", cub->gun5_texture_path);
    printf("F: %d, in rpg r: %d, in g: %d, in b: %d\n", cub->floor_color, (cub->floor_color >> 16) & 0xFF, (cub->floor_color >> 8) & 0xFF, cub->floor_color & 0xFF);
    printf("C: %d, in rpg r: %d, in g: %d, in b: %d\n", cub->sky_color, (cub->sky_color >> 16) & 0xFF, (cub->sky_color >> 8) & 0xFF, cub->sky_color & 0xFF);
}
int check_file_ext(char *file)
{
    int len;

    len = ft_strlen(file);
    if (len < 4 || ft_strncmp(file + len - 4, ".cub", 4) != 0)
    {
        write(2, "[ERROR] Wrong file extension\n", 30);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int parse_map(t_cub3d *cub, int argc, char **argv)
{
    int fd;

    if (argc != 2)
    {
        printf("Error\nWrong number of arguments\n");
        return (EXIT_FAILURE);
    }
    if (check_file_ext(argv[1]) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nFailed to open file\n");
        return (EXIT_FAILURE);
    }
    if(parse_info_part(cub, fd) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    
    if (parse_map_part(cub, fd) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    printf("Map parsed successfully\n");
    print_parse_result_debug(cub);
    exit(0);
    return (EXIT_SUCCESS);
}

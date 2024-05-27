#include "cub3d.h"

void draw_from_above(t_cub3d *cub, int map_width, int map_height, double scale)
{
    int x;
    int y;
    int gap;

    y = 0;
    gap = 1;
    while (y < map_height)
    {
        x = 0;
        while (x < map_width)
        {
            if (cub->map.addr[y][x] == '1')
                draw_square(cub, (t_vec2){((x * TILE_SIZE) + gap) * scale,
                 ((y * TILE_SIZE) + gap) * scale}, 
                 (TILE_SIZE - gap * 2) * scale, 0xFFFFFF80);
            else
                draw_square(cub, (t_vec2){((x * TILE_SIZE) + gap) * scale,
                 ((y * TILE_SIZE) + gap) * scale}, 
                 (TILE_SIZE - gap * 2) * scale, 0x00000080);
            x++;
        }
        y++;
    }
}

void draw_player(t_cub3d *cub)
{
    double scale = cub->minimap_scale;
    draw_circle(cub, (t_vec2){cub->camera.pos.x * scale, cub->camera.pos.y * scale}, 7, 0xFF000080);
}

void draw_bg(t_cub3d *cub)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_pixel_put(cub->image, x, y, cub->sky_color);
            x++;
        }
        y++;
    }
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_pixel_put(cub->image, x, y, cub->floor_color);
            x++;
        }
        y++;
    }
}


void doors_update(t_cub3d *cub)
{
    int i;

    i = 0;
    while (i < MAX_DOORS)
    {
        if (cub->door_infos[i].map_x == -1)
            break;
        if (cub->door_infos[i].is_opening)
        {
            cub->door_infos[i].close_factor -= 0.01;
            if (cub->door_infos[i].close_factor <= 0.2)
            {
                cub->door_infos[i].close_factor = 0.2;
            }
        }
        else
        {
            cub->door_infos[i].close_factor += 0.01;
            if (cub->door_infos[i].close_factor >= 1)
            {
                cub->door_infos[i].close_factor = 1;
            }
        }
        i++;
    }
}

void pre_render(t_cub3d *cub)
{
    doors_update(cub);
    if(cub->display_debug == false)
        draw_bg(cub);
    else 
    {
        ft_clear_image(cub->image);
        draw_from_above(cub, cub->map.width, cub->map.height, cub->minimap_scale);
    }
}

void render(t_cub3d *cub)
{
    double angle;
    double step;
    int rays;

    rays = 0;
    angle = cub->camera.dir - degree_to_radian(cub->camera.fov / 2);
    step = degree_to_radian(cub->camera.fov) / WIDTH;
    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
    while (rays < WIDTH)
    {
        ray_cast(cub, &cub->map, angle, 0xFF0000ff, rays, false);
        angle += step;
        rays++;
        if(angle < 0)
            angle += 2 * M_PI;
        if(angle > 2 * M_PI)
            angle -= 2 * M_PI;
    }
}

void    render_loop_handle(void *param)
{
    t_cub3d *cub;

    cub = (t_cub3d *)param;
    pre_render(cub);
    render(cub);
   if(cub->display_debug == true)
    draw_player(cub);
}

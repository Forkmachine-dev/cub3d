#include "cub3d.h"

// we need to draw the map from up so we can visualize the raycasting
void draw_from_above(t_cub3d *cub)
{
    int map_width = cub->map.width;
    int map_height = cub->map.height;

    int x = 0;
    int y = 0;
    int gap = 1;

    double scale = cub->minimap_scale;
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
    int floor_color = 0x404000FF;
    int sky = 0xF0F0FFff;

    int x = 0;
    int y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_pixel_put(cub->image, x, y, sky);
            x++;
        }
        y++;
    }

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            ft_pixel_put(cub->image, x, y, floor_color);
            x++;
        }
        y++;
    }
}


void doors_update(t_cub3d *cub)
{
    int i = 0;
    while (i < MAX_DOORS)
    {
        if (cub->door_infos[i].map_x == -1)
            break;
        if (cub->door_infos[i].is_opening)
        {
            cub->door_infos[i].close_factor -= 0.01;
            if (cub->door_infos[i].close_factor <= 0)
            {
                cub->door_infos[i].close_factor = 0;
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

void render_loop_handle (void *param)
{
    t_cub3d *cub = (t_cub3d *)param;
    if(cub->display_debug == false)
        draw_bg(cub);
    else 
    {
        ft_clear_image(cub->image);
        draw_from_above(cub);
    }
    doors_update(cub);
    double angle = cub->camera.dir - degree_to_radian(cub->camera.fov / 2);
    double step = degree_to_radian(cub->camera.fov) / WIDTH;
    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
    int rays = 0;
    while (rays < WIDTH)
    {

        ray_cast(cub, &cub->map, angle, 0xFF0000ff, rays);
        angle += step;
        rays++;

        if(angle < 0)
            angle += 2 * M_PI;
        if(angle > 2 * M_PI)
            angle -= 2 * M_PI;
    }
   
  if(cub->display_debug == true)
    draw_player(cub);
}

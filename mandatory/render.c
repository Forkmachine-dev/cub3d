#include "cub3d.h"

// we need to draw the map from up so we can visualize the raycasting
void draw_from_above(t_cub3d *cub)
{
    int map_width = cub->map.width;
    int map_height = cub->map.height;

    int x = 0;
    int y = 0;
    int gap = 1;

    while (y < map_height)
    {
        x = 0;
        while (x < map_width)
        {
            if (cub->map.addr[y][x] == '1')
                draw_square(cub, (t_vec2){((x * TILE_SIZE) + gap) * ZOOM,
                 ((y * TILE_SIZE) + gap) * ZOOM}, 
                 (TILE_SIZE - gap * 2) * ZOOM, 0xFFFFFF80);
            else
                draw_square(cub, (t_vec2){((x * TILE_SIZE) + gap) * ZOOM,
                 ((y * TILE_SIZE) + gap) * ZOOM}, 
                 (TILE_SIZE - gap * 2) * ZOOM, 0x00000080);
            x++;
        }
        y++;
    }


}

void draw_player(t_cub3d *cub)
{
    draw_circle(cub, (t_vec2){cub->camera.pos.x * ZOOM, cub->camera.pos.y * ZOOM}, 7, 0xFF000080);
   // draw the direction of the player
    t_vec2 collison_point_f = {cub->camera.pos.x + cos(cub->camera.dir) * 20, cub->camera.pos.y + sin(cub->camera.dir) * 20};
    t_vec2 collison_point_b = {cub->camera.pos.x - cos(cub->camera.dir) * 20, cub->camera.pos.y - sin(cub->camera.dir) * 20};
    t_vec2 collison_point_l = {cub->camera.pos.x + cos(cub->camera.dir - M_PI_2) * 20, cub->camera.pos.y + sin(cub->camera.dir - M_PI_2) * 20};
    t_vec2 collison_point_r = {cub->camera.pos.x + cos(cub->camera.dir + M_PI_2) * 20, cub->camera.pos.y + sin(cub->camera.dir + M_PI_2) * 20};

    t_vec2 dir_f = {collison_point_f.x * ZOOM, collison_point_f.y * ZOOM};
    t_vec2 dir_b = {collison_point_b.x * ZOOM, collison_point_b.y * ZOOM};
    t_vec2 dir_l = {collison_point_l.x * ZOOM, collison_point_l.y * ZOOM};
    t_vec2 dir_r = {collison_point_r.x * ZOOM, collison_point_r.y * ZOOM};


    if(is_solid_tile(collison_point_f, &cub->map) == true)
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_f, 0x00FF0080);
    else 
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_f, 0x0000FF80);
    
    if(is_solid_tile(collison_point_b, &cub->map) == true)
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_b, 0x00FF0080);
    else 
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_b, 0x0000FF80);

    if(is_solid_tile(collison_point_l, &cub->map) == true)
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_l, 0x00FF0080);
    else 
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_l, 0x0000FF80);

    if(is_solid_tile(collison_point_r, &cub->map) == true)
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_r, 0x00FF0080);
    else 
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM , cub->camera.pos.y * ZOOM}, &dir_r, 0x0000FF80);
}
void draw_bg(t_cub3d *cub)
{
    int floor_color = 0x808000FF;
    int sky = 0xeeeee4;

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

void render_loop_handle (void *param)
{
    t_cub3d *cub = (t_cub3d *)param;
    ft_clear_image(cub->image);
    //draw_from_above(cub);

    draw_bg(cub);
    double angle = cub->camera.dir - degree_to_radian(cub->camera.fov / 2);
    double step = degree_to_radian(cub->camera.fov) / WIDTH;
    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
    int rays = 0;
    while (rays < WIDTH)
    {
        ray_cast(cub, &cub->map, angle, true, 0xFF0000ff, rays);
        angle += step;
        rays++;

        if(angle < 0)
            angle += 2 * M_PI;
        if(angle > 2 * M_PI)
            angle -= 2 * M_PI;
    }
   
   //draw_player(cub);
}
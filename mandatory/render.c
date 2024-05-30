#include "cub3d.h"

void draw_from_above(t_cub3d *cub, int map_width, int map_height, double scale)
{
    int x;
    int y;
    int gap;
    
    y = 0;
    gap = 0;
    (void)gap;
    (void)scale;
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
    draw_circle(cub, (t_vec2){cub->camera.pos.x * scale, cub->camera.pos.y * scale}, 4, 0xFF000080);
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
    draw_bg(cub);
}

void render(t_cub3d *cub)
{
    t_cast_request request;
    double step;

    request.current_ray = 0;
    request.angle = cub->camera.dir - degree_to_radian(cub->camera.fov / 2);
    request.color = 0xFF0000FF;
    request.is_for_collision = false;
    step = degree_to_radian(cub->camera.fov) / WIDTH;
    while (request.current_ray < WIDTH)
    {
        ray_cast(cub, &cub->map, &request);
        request.angle += step;
        request.current_ray++;
    }
}

void update_delta_time(t_cub3d *cub)
{
    double current_time;

    current_time = mlx_get_time();
    cub->delta_time = current_time - cub->last_time;
    cub->last_time = current_time;
}

void render_gun(t_cub3d *cub)
{
    mlx_texture_t *gun_texture;
    uint32_t tex_x;
    uint32_t tex_y;
    uint32_t screen_x;
    uint32_t screen_y;
    int color;

    gun_texture = cub->gun_textures[cub->current_gun_index];
    // we render the gun in the bottom center of the screen
    screen_x = WIDTH / 2 - gun_texture->width / 2;
    screen_y = HEIGHT - gun_texture->height;
    tex_y = 0;
  
    while (tex_y < gun_texture->height && screen_y + tex_y < HEIGHT)
    {
  
        tex_x = 0;
        while (tex_x < gun_texture->width && screen_x + tex_x < WIDTH)
        {
            color = get_color_texture(gun_texture, tex_x, tex_y);
            if (color != 0)
                ft_pixel_put(cub->image, screen_x + tex_x, screen_y + tex_y, color);
            tex_x++;
        }
        tex_y++;
    }

}

void update_gun(t_cub3d *cub)
{
    if (cub->gun_state.is_firing)
    {
        cub->gun_state.sprite_time += cub->delta_time;
        if (cub->gun_state.sprite_time > 0.05)
        {
            cub->gun_state.sprite_time = 0;
            cub->current_gun_index++;
            if (cub->current_gun_index >= 6)
            {
                cub->current_gun_index = 0;
                cub->gun_state.is_firing = false;
            }
        }
    }
}
void    render_loop_handle(void *param)
{
    t_cub3d *cub;


    cub = (t_cub3d *)param;
    update_delta_time(cub);
    pre_render(cub);
    render(cub);
    update_gun(cub);
    render_gun(cub);
    draw_from_above(cub, cub->map.width, cub->map.height, cub->minimap_scale);
    draw_player(cub);
}

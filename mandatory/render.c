#include "cub3d.h"

// we need to draw the map from up so we can visualize the raycasting
void draw_from_above(t_cub3d *cub)
{
    int map_width = cub->map.width;
    int map_height = cub->map.height;

    int x = 0;
    int y = 0;
    int zoom = 70;
    int gap = 1;

    while (y < map_height)
    {
        x = 0;
        while (x < map_width)
        {
            if (cub->map.addr[y][x] == '1')
                draw_square(cub, (t_vec2){(x * zoom) + gap, (y * zoom) + gap}, zoom - gap * 2, 0xFFFFFFFF);
            else
                draw_square(cub, (t_vec2){(x * zoom) + gap, (y * zoom) + gap}, zoom - gap * 2, 0x000000FF);
            x++;
        }
        y++;
    }
    draw_circle(cub, (t_vec2){cub->camera.pos.x * zoom + zoom / 2, cub->camera.pos.y * zoom + zoom / 2}, zoom / 9, 0xFF0000FF);
    // draw the direction of the player
    t_vec2 dir = {cub->camera.pos.x * zoom + zoom / 2 + cos(cub->camera.dir) * zoom / 2, cub->camera.pos.y * zoom + zoom / 2 + sin(cub->camera.dir) * zoom / 2};
    ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * zoom + zoom / 2, cub->camera.pos.y * zoom + zoom / 2}, &dir, 0xFF0000FF);

}


void render_loop_handle (void *param)
{
    t_cub3d *cub = (t_cub3d *)param;
    ft_clear_image(cub->image);
    draw_from_above(cub);

    if (cub->should_terminate == 1)
        mlx_close_window(cub->mlx);
}
#include "cub3d.h"

void draw_square(t_cub3d *cub, t_vec2 pos, int size, int color)
{
    int i = 0;
    while(i < size)
    {
        int j = 0;
        while(j < size)
        {
            ft_pixel_put(cub->image, pos.x + i, pos.y + j, color);
            j++;
        }
        i++;
    }
}

void draw_ring(t_cub3d *cub, t_vec2 pos, int radius, int color)
{
    float current_angle = 0;
    float angle_step = 0.01; // Adjust this for smoothness vs. performance

    while (current_angle < 2 * M_PI)
    {
        float cos_angle = cos(current_angle);
        float sin_angle = sin(current_angle);
        t_vec2 point = {pos.x + radius * cos_angle, pos.y + radius * sin_angle};
        ft_pixel_put(cub->image, point.x, point.y, color);
        current_angle += angle_step;
    }
}

void draw_circle(t_cub3d *cub, t_vec2 pos, int radius, int color)
{
    int current_radius = 0;

    while (current_radius <= radius)
    {
        draw_ring(cub, pos, current_radius, color);
        current_radius++;
    }
}


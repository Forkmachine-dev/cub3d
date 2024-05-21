#include "cub3d.h"

void  ft_key_hooks(void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    float move_x = 0;
    float move_y = 0;
    float move_speed = 5;

    int closeset_hit = ray_cast(cub, &cub->map, cub->camera.dir, true, 0xFFFF00FF, 0);

    if(closeset_hit < 20)
        move_speed = 0;

    if(mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
    {
        cub->camera.dir += 0.1;
        if (cub->camera.dir > 2 * M_PI)
            cub->camera.dir -= 2 * M_PI;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
    {
        cub->camera.dir -= 0.1;
        if (cub->camera.dir < 0)
            cub->camera.dir += 2 * M_PI;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_W))
    {
        move_x += cos(cub->camera.dir);
        move_y += sin(cub->camera.dir) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_S))
    {
        move_x -= cos(cub->camera.dir) ;
        move_y -= sin(cub->camera.dir) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_A))
    {
        move_x += cos(cub->camera.dir - M_PI_2) ;
        move_y += sin(cub->camera.dir - M_PI_2) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_D))
    {
        move_x += cos(cub->camera.dir + M_PI_2) ;
        move_y += sin(cub->camera.dir + M_PI_2) ;
    }
        // Normalize the movement when moving diagonally
    if (move_x != 0 && move_y != 0)
    {
        float length = sqrt(move_x * move_x + move_y * move_y);
        move_x /= length;
        move_y /= length;
    }

    // Apply the movement
    cub->camera.pos.x += move_x * move_speed;
    cub->camera.pos.y += move_y * move_speed;

    if(mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(cub->mlx);
    }
}
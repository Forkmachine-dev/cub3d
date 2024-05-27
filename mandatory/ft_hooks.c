#include "cub3d.h"

void  ft_key_hooks(void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    float move_x = 0;
    float move_y = 0;
    float move_speed = 4;
    float rot_speed = 0.07;

    int dist_w = ray_cast(cub, &cub->map, cub->camera.dir, 0, 0x0000FFFF, true);
    if(mlx_is_key_down(cub->mlx, MLX_KEY_E) && cub->is_current_ray_door && dist_w < TILE_SIZE * 2)
    {
        cub->door_infos[cub->current_ray_door_index].is_opening = !cub->door_infos[cub->current_ray_door_index].is_opening;
    }
    if(cub->is_current_ray_door && cub->door_infos[cub->current_ray_door_index].close_factor <= 0.21)
        dist_w = 30; // allow to move through the door

    int dist_s = ray_cast(cub, &cub->map, cub->camera.dir + M_PI, 0, 0x0000FFFF, false);
    int dist_a = ray_cast(cub, &cub->map, cub->camera.dir - M_PI_2, 0, 0x0000FFFF, false);
    int dist_d = ray_cast(cub, &cub->map, cub->camera.dir + M_PI_2, 0, 0x0000FFFF, false);


 

    if(mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
    {
        cub->camera.dir += rot_speed;
        if (cub->camera.dir > 2 * M_PI)
            cub->camera.dir -= 2 * M_PI;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_LEFT) )
    {
        cub->camera.dir -= rot_speed;
        if (cub->camera.dir < 0)
            cub->camera.dir += 2 * M_PI;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_W) && dist_w > 20)
    {
        move_x += cos(cub->camera.dir);
        move_y += sin(cub->camera.dir) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_S) && dist_s > 20)
    {
        move_x -= cos(cub->camera.dir) ;
        move_y -= sin(cub->camera.dir) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_A) && dist_a > 20)
    {
        move_x += cos(cub->camera.dir - M_PI_2) ;
        move_y += sin(cub->camera.dir - M_PI_2) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_D) && dist_d > 20)
    {
        move_x += cos(cub->camera.dir + M_PI_2) ;
        move_y += sin(cub->camera.dir + M_PI_2) ;
    }

    if(mlx_is_key_down(cub->mlx, MLX_KEY_SPACE))
        cub->display_debug = true;
    else
        cub->display_debug = false;
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
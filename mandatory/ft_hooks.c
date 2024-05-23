#include "cub3d.h"



// bool x_y_move_check(float x, float y, t_map *map)
// {
//     int x_tile = x / TILE_SIZE;
//     int y_tile = y / TILE_SIZE;

//     if (x_tile <= 0 || y_tile <= 0 || x_tile >= map->width || y_tile >= map->height)
//         return false;
//     if (map->addr[y_tile][x_tile] == '1')
//         return false;
//     return true;
// }

// void check_and_move_up(t_cub3d *cub, float next_x, float next_y, bool pos_dir)
// {
//     t_vec2 cam = cub->camera.pos;
//     if(x_y_move_check(cam.x + next_x * 5, cam.y, &cub->map))
//     {
//         cam.x += next_x;
//     }
//     if(x_y_move_check(cam.x, cam.y + next_y * 5, &cub->map))
//     {
//         cam.y += next_y;
//     }

//     cub->camera.pos = cam;
// }

// void check_and_move_down(t_cub3d *cub, float next_x, float next_y, bool pos_dir)
// {
//     t_vec2 cam = cub->camera.pos;
//     if(x_y_move_check(cam.x - next_x * 5, cam.y, &cub->map))
//     {
//         cam.x -= next_x;
//     }
//     if(x_y_move_check(cam.x, cam.y - next_y * 5, &cub->map))
//     {
//         cam.y -= next_y;
//     }

//     cub->camera.pos = cam;
// }
// void check_and_move(t_cub3d *cub, float next_x, float next_y, bool pos_dir)
// {
//     t_vec2 cam = cub->camera.pos;
//     t_map* map = &cub->map;
//     if((((next_x * 5) + cam.x ) > map->width * TILE_SIZE) || (((next_y * 5) + cam.y) > map->height * TILE_SIZE))
//         return;
//     if(pos_dir)
//     {
//         check_and_move_up(cub, next_x, next_y, pos_dir);
//     }
//     else
//     {
//         check_and_move_down(cub, next_x, next_y, pos_dir);
//     }
// }

void  ft_key_hooks(void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    float move_x = 0;
    float move_y = 0;
    float move_speed = 4;
    float rot_speed = 0.07;

    int dist_w = ray_cast(cub, &cub->map, cub->camera.dir, false, 0, 0x0000FFFF);
    int dist_s = ray_cast(cub, &cub->map, cub->camera.dir + M_PI, false, 0, 0x0000FFFF);
    int dist_a = ray_cast(cub, &cub->map, cub->camera.dir - M_PI_2, false, 0, 0x0000FFFF);
    int dist_d = ray_cast(cub, &cub->map, cub->camera.dir + M_PI_2, false, 0, 0x0000FFFF);

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
    if(mlx_is_key_down(cub->mlx, MLX_KEY_W) && dist_w > 5)
    {
        move_x += cos(cub->camera.dir);
        move_y += sin(cub->camera.dir) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_S) && dist_s > 5)
    {
        move_x -= cos(cub->camera.dir) ;
        move_y -= sin(cub->camera.dir) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_A) && dist_a > 5)
    {
        move_x += cos(cub->camera.dir - M_PI_2) ;
        move_y += sin(cub->camera.dir - M_PI_2) ;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_D) && dist_d > 5)
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
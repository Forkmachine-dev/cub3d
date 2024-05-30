#include "cub3d.h"


void fire_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
    t_cub3d *cub = (t_cub3d *)param;

    (void)mods;
    if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
    {
        cub->gun_state.is_firing = true;
    }
}

void open_door(mlx_key_data_t key, t_cub3d *cub)
{
    t_cast_request req;
    req.angle = cub->camera.dir;
    req.color = 0x0000FFFF;
    req.current_ray = 0;
    req.is_for_collision = true;
    float dist = ray_cast(cub, &cub->map, &req);
    if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
    {
        if(cub->cast_result.current_ray_is_door && dist < TILE_SIZE * 2)
        {
         cub->door_infos[cub->cast_result.current_ray_door_index].is_opening = !cub->door_infos[cub->cast_result.current_ray_door_index].is_opening;
        }
    }
}

void look_unlock_mouse(mlx_key_data_t key, void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    if (key.key == MLX_KEY_F && key.action == MLX_PRESS)
    {
        if(cub->mouse_locked)
        {
            cub->mouse_locked = false;
            mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_NORMAL);
        }
        else
        {
            cub->mouse_locked = true;
            mlx_set_cursor_mode(cub->mlx, MLX_MOUSE_HIDDEN);
        }
        mlx_set_mouse_pos(cub->mlx, cub->mlx->width / 2, cub->mlx->height / 2);
    }
}

void key_pess_hook(mlx_key_data_t key, void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    open_door(key, cub);
    look_unlock_mouse(key, cub);
}

void  ft_key_hooks(void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    float move_x = 0;
    float move_y = 0;
    float move_speed = 4;
    float rot_speed = 0.07;

    t_cast_request request;
    request.angle = cub->camera.dir;
    request.color = 0x0000FFFF;
    request.current_ray = 0;
    request.is_for_collision = true;

    float dist_w = ray_cast(cub, &cub->map, &request);
    if(cub->cast_result.current_ray_is_door && cub->door_infos[cub->cast_result.current_ray_door_index].close_factor <= 0.21)
        dist_w = 30; // allow to move through the door
    request.angle = cub->camera.dir + M_PI;
    float dist_s = ray_cast(cub, &cub->map, &request);
    request.angle = cub->camera.dir - M_PI_2;
    float dist_a = ray_cast(cub, &cub->map, &request);
    request.angle = cub->camera.dir + M_PI_2;
    float dist_d = ray_cast(cub, &cub->map, &request);

 

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

    if (move_x != 0 && move_y != 0)
    {
        float length = sqrt(move_x * move_x + move_y * move_y);
        move_x /= length;
        move_y /= length;
    }

    // Apply the movement
    cub->camera.pos.x += move_x * move_speed;
    cub->camera.pos.y += move_y * move_speed;

    if(cub->mouse_locked)
    {
        int x, y;
        mlx_get_mouse_pos(cub->mlx, &x, &y);
        mlx_set_mouse_pos(cub->mlx, cub->mlx->width / 2, cub->mlx->height / 2);
        cub->camera.dir += (cub->mlx->width / 2 - x) * (-0.01 * cub->delta_time);
    }

    if(mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(cub->mlx);
    }

}
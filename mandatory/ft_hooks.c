/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:39:32 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/05/30 21:50:33 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
         cub->door_infos[cub->cast_result.current_ray_door_index].is_opening =
            !cub->door_infos[cub->cast_result.current_ray_door_index].is_opening;
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
    if(key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
        mlx_close_window(cub->mlx);
}

void roatate_view(t_cub3d *cub)
{
    float rot_speed;
    
    rot_speed = 0.07;
    
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
    if(cub->mouse_locked)
    {
        int x, y;
        mlx_get_mouse_pos(cub->mlx, &x, &y);
        mlx_set_mouse_pos(cub->mlx, cub->mlx->width / 2, cub->mlx->height / 2);
        cub->camera.dir += (cub->mlx->width / 2 - x) * (-0.01 * cub->delta_time);
    }
}

void solve_distances(t_cub3d *cub, float *distances)
{
    t_cast_request request;
    float close_factor;
    
    request.angle = cub->camera.dir;
    request.color = 0xFF0000FF;
    request.is_for_collision = true;
    distances[0] = ray_cast(cub, &cub->map, &request);
    close_factor = cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
    if(cub->cast_result.current_ray_is_door && close_factor <= 0.21)
        distances[0] = 30;
    request.angle = cub->camera.dir + M_PI;
    distances[1] = ray_cast(cub, &cub->map, &request);
    close_factor = cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
    if(cub->cast_result.current_ray_is_door && close_factor <= 0.21)
        distances[1] = 30;
    request.angle = cub->camera.dir - M_PI_2;
    distances[2] = ray_cast(cub, &cub->map, &request);
    close_factor = cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
    if(cub->cast_result.current_ray_is_door && close_factor <= 0.21)
        distances[2] = 30;
    request.angle = cub->camera.dir + M_PI_2;
    distances[3] = ray_cast(cub, &cub->map, &request);
    close_factor = cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
    if(cub->cast_result.current_ray_is_door && close_factor <= 0.21)
        distances[3] = 30;
}

void calculate_movement(t_cub3d *cub, float *distances, t_vec2 *move)
{
    move->x = 0;
    move->y = 0;
    if(mlx_is_key_down(cub->mlx, MLX_KEY_W) && distances[0] > 20)
    {
        move->x += cos(cub->camera.dir);
        move->y += sin(cub->camera.dir);
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_S) && distances[1] > 20)
    {
        move->x += cos(cub->camera.dir + M_PI);
        move->y += sin(cub->camera.dir + M_PI);
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_A) && distances[2] > 20)
    {
        move->x += cos(cub->camera.dir - M_PI_2);
        move->y += sin(cub->camera.dir - M_PI_2);
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_D) && distances[3] > 20)
    {
        move->x += cos(cub->camera.dir + M_PI_2);
        move->y += sin(cub->camera.dir + M_PI_2);
    }
}

void normalize_movement(t_vec2 *move)
{
    float length;
    
    if (move->x != 0 && move->y != 0)
    {
        length = sqrt(move->x * move->x + move->y * move->y);
        move->x /= length;
        move->y /= length;
    }
}

void apply_movement(t_cub3d *cub, t_vec2 *move)
{
    float move_speed = 4;
    
    cub->camera.pos.x += move->x * move_speed;
    cub->camera.pos.y += move->y * move_speed;
}

void movement(t_cub3d *cub)
{
    float distances[4];
    t_vec2 move;

    solve_distances(cub, distances);
    calculate_movement(cub, distances, &move);
    normalize_movement(&move);
    apply_movement(cub, &move);
}

void  ft_key_hooks(void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    roatate_view(cub);
    movement(cub);
}
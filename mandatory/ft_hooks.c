#include "cub3d.h"

void  ft_key_hooks(void *param)
{
    t_cub3d *cub = (t_cub3d *)param;

    if(mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
    {
        cub->camera.dir += 0.1;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
    {
        cub->camera.dir -= 0.1;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_W))
    {
        cub->camera.pos.x += cos(cub->camera.dir) * 0.1;
        cub->camera.pos.y += sin(cub->camera.dir) * 0.1;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_S))
    {
        cub->camera.pos.x -= cos(cub->camera.dir) * 0.1;
        cub->camera.pos.y -= sin(cub->camera.dir) * 0.1;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_A))
    {
        cub->camera.pos.x += cos(cub->camera.dir - M_PI_2) * 0.1;
        cub->camera.pos.y += sin(cub->camera.dir - M_PI_2) * 0.1;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_D))
    {
        cub->camera.pos.x += cos(cub->camera.dir + M_PI_2) * 0.1;
        cub->camera.pos.y += sin(cub->camera.dir + M_PI_2) * 0.1;
    }
    if(mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
    {
        cub->should_terminate = 1;
    }
}
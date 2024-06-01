#include "cub3d.h"


int terminate_cub3d(t_cub3d *cub)
{
    if(cub->mlx)
        mlx_close_window(cub->mlx);
    if(cub->image)
        mlx_delete_image(cub->mlx, cub->image);
    free_cub(cub);
    ft_bzero(cub, sizeof(t_cub3d));
    return (EXIT_SUCCESS);
}
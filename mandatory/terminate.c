#include "cub3d.h"


int terminate_cub3d(t_cub3d *cub)
{
    mlx_close_window(cub->mlx);
    mlx_delete_image(cub->mlx, cub->image);
    free_cub(cub);
    return (EXIT_SUCCESS);
}
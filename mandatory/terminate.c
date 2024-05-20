#include "cub3d.h"

int terminate_cub3d(t_cub3d *cub)
{
    mlx_close_window(cub->mlx);
    return (EXIT_SUCCESS);
}
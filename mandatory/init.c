#include "cub3d.h"


int init_cub3d(t_cub3d *cub)
{
    ft_bzero(cub, sizeof(t_cub3d));
	if (!(cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    mlx_loop_hook(cub->mlx, render_loop_handle, cub);
    mlx_loop_hook(cub->mlx, ft_key_hooks, cub);
    return (EXIT_SUCCESS);
}
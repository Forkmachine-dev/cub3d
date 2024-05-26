#include "cub3d.h"


int init_cub3d(t_cub3d *cub)
{
    ft_bzero(cub, sizeof(t_cub3d));
	if (!(cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false)))
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
	cub->display_debug = false;
	cub->north_texture = mlx_load_png("textures/wall_no.png");
	cub->south_texture = mlx_load_png("textures/wall_so.png");
	cub->west_texture = mlx_load_png("textures/wall_we.png");
	cub->east_texture = mlx_load_png("textures/wall_ea.png");
	cub->door_texture = mlx_load_png("textures/door.png");

	if(!cub->north_texture || !cub->south_texture || !cub->west_texture || !cub->east_texture)
	 	printf("Error loading textures\n");

    return (EXIT_SUCCESS);
}
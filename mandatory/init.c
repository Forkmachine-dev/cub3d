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
	mlx_key_hook(cub->mlx, key_pess_hook, cub);
	mlx_mouse_hook(cub->mlx, fire_mouse_hook, cub);
    mlx_loop_hook(cub->mlx, render_loop_handle, cub);
    mlx_loop_hook(cub->mlx, ft_key_hooks, cub);
	cub->north_texture = mlx_load_png("textures/wall_no.png");
	cub->south_texture = mlx_load_png("textures/wall_so.png");
	cub->west_texture = mlx_load_png("textures/wall_we.png");
	cub->east_texture = mlx_load_png("textures/wall_ea.png");
	cub->door_texture = mlx_load_png("textures/door.png");

	cub->gun_textures[0] = mlx_load_png("textures/gun0.png");
	cub->gun_textures[1] = mlx_load_png("textures/gun1.png");
	cub->gun_textures[2] = mlx_load_png("textures/gun2.png");
	cub->gun_textures[3] = mlx_load_png("textures/gun3.png");
	cub->gun_textures[4] = mlx_load_png("textures/gun4.png");
	cub->gun_textures[5] = mlx_load_png("textures/gun5.png");

	//check if all textures are loaded
	int i = 0;
	while(i < 6)
	{
		if(!cub->gun_textures[i])
		{
			printf("Error loading gun texture %d\n", i);
			return(EXIT_FAILURE);
		}
		i++;
	}
	
	cub->current_gun_index = 0;
	cub->gun_state.is_firing = false;
	cub->gun_state.sprite_time = 0;

	cub->last_time = mlx_get_time();

	cub->sky_color = 0xF0F0FFFF;
	cub->floor_color = 0x404000FF;

	if(!cub->north_texture || !cub->south_texture || !cub->west_texture || !cub->east_texture)
	 	printf("Error loading textures\n");

    return (EXIT_SUCCESS);
}
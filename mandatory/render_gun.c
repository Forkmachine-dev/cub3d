/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:08:10 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:22:35 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_gun(t_cub3d *cub, mlx_texture_t	*gun_texture)
{
	uint32_t		tex_x;
	uint32_t		tex_y;
	uint32_t		screen_x;
	uint32_t		screen_y;
	int				color;

	gun_texture = cub->gun_textures[cub->current_gun_index];
	screen_x = WIDTH / 2 - gun_texture->width / 2;
	screen_y = HEIGHT - gun_texture->height;
	tex_y = 0;
	while (tex_y < gun_texture->height && screen_y + tex_y < HEIGHT)
	{
		tex_x = 0;
		while (tex_x < gun_texture->width && screen_x + tex_x < WIDTH)
		{
			color = get_color_texture(gun_texture, tex_x, tex_y);
			if (color != 0)
				ft_pixel_put(cub->image, screen_x + tex_x, screen_y + tex_y,
					color);
			tex_x++;
		}
		tex_y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:54:13 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:25:23 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t	get_color_texture(mlx_texture_t *txt, int x, int y)
{
	int		color;
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	if (x < 0 || y < 0 || x >= (int)txt->width || y >= (int)txt->height)
		return (0x00000000);
	color = ((y * txt->bytes_per_pixel) * txt->width + (x
				* txt->bytes_per_pixel));
	r = txt->pixels[color];
	g = txt->pixels[color + 1];
	b = txt->pixels[color + 2];
	a = txt->pixels[color + 3];
	return (create_rgba(r, g, b, a));
}

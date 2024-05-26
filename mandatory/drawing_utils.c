/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:02:20 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/05/24 01:54:56 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_inside_screen(t_vec2 *vec)
{
	return (vec->x >= 0 && vec->x < WIDTH && vec->y >= 0 && vec->y < HEIGHT);
}

void	ft_pixel_put(mlx_image_t *img, int x, int y, int color)
{
    if (is_inside_screen(&(t_vec2){x, y}))
     mlx_put_pixel(img, x, y, color);
}

void	ft_render_image(t_cub3d *cub)
{
	mlx_image_to_window(cub->mlx,
		cub->image, 0, 0);
}



void	ft_draw_line(t_cub3d *instance, const t_vec2 *a, const t_vec2 *b, int color)
{
    int			i;
    float		num_points;
    t_vec2	v;
    t_vec2	increment;
    t_vec2	d_vector;

    d_vector.x = (b->x - a->x);
    d_vector.y = (b->y - a->y);
    num_points = ft_fmax(fabsf(d_vector.x), fabsf(d_vector.y));
    increment.x = d_vector.x / num_points;
    increment.y = d_vector.y / num_points;
    v.x = a->x;
    v.y = a->y;
    i = 0;
    while (i <= num_points)
    {
        ft_pixel_put(instance->image, v.x, v.y, color);
        i++;
        v.x += increment.x;
        v.y += increment.y;
    }
}

void	ft_clear_image(mlx_image_t *image)
{
    int i;
    int j;

    i = 0;
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            ft_pixel_put(image, j, i, 0x000000);
            j++;
        }
        i++;
    }
}

int create_rgba(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return ((r << 24) | (g << 16) | (b << 8) | a);
}

int32_t    get_color_texture(mlx_texture_t *txt, int x, int y)
{
    if(x < 0 || y < 0 || x >= (int)txt->width || y >= (int)txt->height)
        return (0x00000000); // return black (0, 0, 0, 0
    int        color;
    int32_t    r;
    int32_t    g;
    int32_t    b;
    int32_t    a;

    color = ((y * txt->bytes_per_pixel) * txt->width + (x
                * txt->bytes_per_pixel));
    r = txt->pixels[color];
    g = txt->pixels[color + 1];
    b = txt->pixels[color + 2];
    a = txt->pixels[color + 3];
    return (create_rgba(r, g, b, a));
}


#ifndef CUB3D_H
# define CUB3D_H

#include "../shared/libft/libft.h"
#include "../shared/mlx_include/MLX42/MLX42.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WIDTH 1920
#define HEIGHT 1080


#define TILE_SIZE 64
#define ZOOM 1


typedef struct s_ray
{
    float hit_x;
    float hit_y;
    float distance;
    float angle;
    bool is_vertical;
    bool is_up;
    bool is_right;

}              t_ray;

typedef struct s_vector
{
    float x;
    float y;
}               t_vec2;

typedef struct s_map
{
    char **addr;
    int width;
    int height;
}               t_map;

typedef struct s_camera
{
    t_vec2  pos;
    double  dir;
    int     fov;
}               t_camera;

typedef struct s_cub3d
{
    mlx_t    *mlx;
    mlx_image_t    *image;
    char    *title;
    t_camera camera;
    t_map map;
}               t_cub3d;

int init_cub3d(t_cub3d *cub);
void ft_init_image(mlx_t* mlx,mlx_image_t *in);
void ft_pixel_put(mlx_image_t *img, int x, int y, int color);
void ft_render_image(t_cub3d *cub);
int is_inside_screen(t_vec2 *vec);
void ft_draw_line(t_cub3d *instance, const t_vec2 *a, const t_vec2 *b, int color);
void ft_clear_image(mlx_image_t *image);
void render_loop_handle (void *param);
int	ft_max(int a, int b);
float ft_fmax(float a, float b);
int	abs(int a);
int terminate_cub3d(t_cub3d *cub);
void draw_square(t_cub3d *cub, t_vec2 pos, int size, int color);
void draw_circle(t_cub3d *cub, t_vec2 pos, int radius, int color);
double	degree_to_radian(double angle_degrees);
void  ft_key_hooks(void *param);
int ray_cast(t_cub3d *cub, t_map *map, double angle, bool debug, int color, int current_ray);
bool is_solid_tile(t_vec2 inter, t_map *map);

#endif
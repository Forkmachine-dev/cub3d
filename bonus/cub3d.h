/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:40:16 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 21:53:03 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../shared/libft/libft.h"
# include "/Users/mel-akhd/mlx/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

# define WIDTH 1920
# define HEIGHT 1080

# define TILE_SIZE 64
# define MAX_DOORS 40

typedef struct s_vector
{
	float							x;
	float							y;
}									t_vec2;

typedef struct s_ivector
{
	int								x;
	int								y;
}									t_ivec2;

typedef struct s_map_row
{
	char							*row;
	int								size;
	struct s_map_row				*up_row;
	struct s_map_row				*down_row;
}									t_map_row;

typedef struct s_parsing_checklist
{
	bool							duplicated_components;
	bool							wrong_texture_ext;
	bool							floor_color;
	bool							sky_color;
	bool							invalid_key;

}									t_parsing_checklist;

typedef struct s_duplication_checklist
{
	char							*component;
	struct s_duplication_checklist	*next;

}									t_duplication_checklist;
typedef struct s_map
{
	char							**addr;
	int								width;
	int								height;
}									t_map;

typedef struct s_direction
{
	bool							up;
	bool							left;
	bool							down;
	bool							right;
}									t_direction;

typedef struct s_camera
{
	t_vec2							pos;
	double							dir;
	int								fov;
}									t_camera;

typedef struct s_door_info
{
	int								map_x;
	int								map_y;
	float							close_factor;
	bool							is_vertical;
	bool							is_opening;
}									t_door_info;

typedef struct s_cast_request
{
	double							angle;
	int								color;
	int								current_ray;
	bool							is_for_collision;
}									t_cast_request;

typedef struct s_cast_result
{
	double							angle;
	double							xo;
	double							yo;
	int								current_ray;
	bool							is_for_collision;
	bool							is_vertical;
	bool							current_ray_is_door;
	int								current_ray_door_index;
	double							dist;
	t_direction						direction;
	t_vec2							inter;

}									t_cast_result;

typedef struct s_wall_render_info
{
	double							wall_height;
	double							wall_top;
	double							hit_x;
	double							hit_y;
	float							tex_x;
	float							tex_y;
	double							tex_y_step;
	mlx_texture_t					*texture;

}									t_wall_render_info;

typedef struct s_gun_state
{
	bool							is_firing;
	double							sprite_time;
}									t_gun_state;

typedef struct s_cub3d
{
	mlx_t							*mlx;
	mlx_image_t						*image;
	mlx_texture_t					*north_texture;
	mlx_texture_t					*south_texture;
	mlx_texture_t					*west_texture;
	mlx_texture_t					*east_texture;
	mlx_texture_t					*door_texture;
	mlx_texture_t					*gun_textures[6];
	t_cast_result					cast_result;
	t_camera						camera;
	t_door_info						door_infos[MAX_DOORS];
	t_map							map;
	t_ivec2							mouse_pos;
	t_gun_state						gun_state;
	t_parsing_checklist				parsing_checklist;
	t_duplication_checklist			*duplication_checklist;
	char							*no_texture_path;
	char							*so_texture_path;
	char							*we_texture_path;
	char							*ea_texture_path;
	char							*gun0_texture_path;
	char							*gun1_texture_path;
	char							*gun2_texture_path;
	char							*gun3_texture_path;
	char							*gun4_texture_path;
	char							*gun5_texture_path;
	char							*door_texture_path;
	int								current_gun_index;
	int								sky_color;
	int								floor_color;
	bool							mouse_locked;
	double							delta_time;
	double							last_time;
	double							minimap_scale;
}									t_cub3d;

int		init_cub3d(t_cub3d *cub);
void	ft_init_image(mlx_t *mlx, mlx_image_t *in);
void	ft_pixel_put(mlx_image_t *img, int x, int y, int color);
void	ft_render_image(t_cub3d *cub);
int		is_inside_screen(t_vec2 *vec);
void	ft_draw_line(t_cub3d *instance, const t_vec2 *a, const t_vec2 *b,
			int color);
void	ft_clear_image(mlx_image_t *image);
void	render_loop_handle(void *param);
int		ft_max(int a, int b);
float	ft_fmax(float a, float b);
int		abs(int a);
int		terminate_cub3d(t_cub3d *cub);
void	draw_square(t_cub3d *cub, t_vec2 pos, int size, int color);
void	draw_circle(t_cub3d *cub, t_vec2 pos, int radius, int color);
double	degree_to_radian(double angle_degrees);
void	ft_key_hooks(void *param);
float	ray_cast(t_cub3d *cub, t_map *map, t_cast_request *request);
int32_t	get_color_texture(mlx_texture_t *txt, int x, int y);
void	key_pess_hook(mlx_key_data_t key, void *param);
void	fire_mouse_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);
int		parse_map(t_cub3d *cub, int argc, char **argv);
int		perr(char *message);
int		parse_info_part(t_cub3d *cub, int fd);
int		parse_map_part(t_cub3d *cub, int fd);
int		skip_spaces(char **line);
int		is_space(char c);
int		check_textures_and_colors(t_cub3d *cub);
void	put_terminator_at_newline(char *line);
int		dup_checklist(t_duplication_checklist **list, char *component);
int		get_image_path(t_cub3d *cub, char **dist, char *line);
int		is_door_valid(t_map_row *map_row);
int		is_player_valid(t_map_row *map_row);
int		up_valid(t_map_row *up, int at);
int		down_valid(t_map_row *down, int at);
int		is_map_valid(t_map_row *map_row);
char	*skip_empty_lines(int fd);
int		is_valid_char(char c);
int		one_or_space(char c);
void	solve_colors(t_cub3d *cub, char *line, int i, int *solved);
int		fill_door_data(t_cub3d *cub);
int		find_player(t_cub3d *cub);
int		determin_scale(t_cub3d *cub);
void	free_cub(t_cub3d *cub);
void	free_duplication_checklist(t_duplication_checklist 
			*duplication_checklist);
void	movement(t_cub3d *cub);
void	roatate_view(t_cub3d *cub);
void	solve_distances(t_cub3d *cub, float *distances);
bool	is_solid_tile(t_vec2 point, t_map *map, t_cub3d *cub,
			t_cast_result *res);
void	solve_h_intersections(t_cub3d *cub, t_map *map,
			t_cast_result *res);
void	solve_v_intersections(t_cub3d *cub, t_map *map, t_cast_result *res);
void	init_cast_result(t_cast_result *cast_result, t_cast_request *request);
void	normalize_angle(double *angle);
void	render_execute(t_cub3d *cub, t_cast_result *res);
void	render_door(t_cub3d *cub, t_cast_result *res, t_wall_render_info *wr);
void	update_delta_time(t_cub3d *cub);
void	doors_update(t_cub3d *cub);
void	update_gun(t_cub3d *cub);
void	render_gun(t_cub3d *cub, mlx_texture_t *gun_texture);
void	draw_from_above(t_cub3d *cub, int map_width, int map_height,
			double scale);
void	draw_player(t_cub3d *cub);
bool	evaluate_key(t_cub3d *cub, char *line, int i, int *solved);

#endif
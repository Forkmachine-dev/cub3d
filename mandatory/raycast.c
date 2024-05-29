#include "cub3d.h"

bool is_solid_tile(t_vec2 point, t_map *map, t_cub3d* cub, t_cast_result *res)
{
    int x = point.x / TILE_SIZE;
    int y = point.y / TILE_SIZE;

    t_vec2 pushed_point = {res->inter.x + (res->xo / 2), res->inter.y + (res->yo / 2)};

    if (x <= 0 || y <= 0 || x >= map->width - 1 || y >= map->height - 1)
        return true;
    if(map->addr[y][x] == '1')
        return true;

    if (map->addr[y][x] == 'V' || map->addr[y][x] == 'H')
    {
        if (map->addr[y][x] == 'V' || map->addr[y][x] == 'H') //NOTE : remove this for loop, use while
        {
            for (int i = 0; i < MAX_DOORS; i++)
            {
                if (cub->door_infos[i].map_x == x && cub->door_infos[i].map_y == y)
                {
                    if((res->is_vertical && !cub->door_infos[i].is_vertical) || (!res->is_vertical && cub->door_infos[i].is_vertical))
                        return false;
                    if(res->is_for_collision)
                    {
                        res->current_ray_is_door = true;
                        res->current_ray_door_index = i;
                        return true;
                    }
                    {
                        if(cub->door_infos[i].is_vertical)
                        {
                            float x_factor = pushed_point.y - ((int)(pushed_point.y / TILE_SIZE) * TILE_SIZE);
                            x_factor = (TILE_SIZE - x_factor) / TILE_SIZE;
                            if(x_factor > 1)
                                x_factor = 1;
                            if(x_factor > cub->door_infos[i].close_factor)
                                    return false;
                            res->inter = pushed_point;
                        }
                        else
                        {
                            float y_factor = pushed_point.x - ((int)(pushed_point.x / TILE_SIZE) * TILE_SIZE);
                            y_factor = y_factor / TILE_SIZE;
                            if(y_factor > cub->door_infos[i].close_factor)
                                    return false;  
                            res->inter = pushed_point;                     
                        }
                        res->current_ray_is_door = true;
                        res->current_ray_door_index = i;
                        break;
                    }
                }
            }
        }
        return true;
    }
    return false;
}


// void render_wall_old(t_cub3d *cub, double dist, double ray_angle, bool is_vertical, int current_ray, float hitX, float hitY)
// {
//     dist = dist * cos(ray_angle - cub->camera.dir);
//     float distance_projection_plane = (WIDTH / 2) / tanf(degree_to_radian(cub->camera.fov / 2));
//     double wall_height = (TILE_SIZE / dist)  *  distance_projection_plane;


  
   
//     int wall_start_top_y = (HEIGHT /2 ) - ((int)wall_height / 2);
//     int wall_start_top_x = current_ray;;

//     float x_factor = 0;
//     float tex_x = 0;

//     mlx_texture_t *texture = NULL;

//     if (is_vertical)
//     {
//         //if down
//         x_factor = hitY - ((int)(hitY / TILE_SIZE) * TILE_SIZE);
//         if (cos(ray_angle) >= 0)
//         {
 
//             texture = cub->east_texture;
//             tex_x = (cub->east_texture->width * x_factor) / TILE_SIZE;

//         }
//         else 
//         {
//             x_factor = (cub->west_texture->width * x_factor) / TILE_SIZE;
//             tex_x = cub->west_texture->width - x_factor;
//             texture = cub->west_texture;
            
//         }

      
//     }
//     else
//     {
//         x_factor = hitX - ((int)(hitX / TILE_SIZE) * TILE_SIZE);
//         if(sin(ray_angle) < 0)
//         {
  
//             texture = cub->north_texture;
//             tex_x = (cub->north_texture->width * x_factor) / TILE_SIZE;
            
//         }
//         else 
//         {
 
//             x_factor = (cub->south_texture->width * x_factor) / TILE_SIZE;
//             tex_x = cub->south_texture->width - x_factor;
//             texture = cub->south_texture;
            
//         }


//     }



//     float tex_y_off = 0;   
//     float tex_y_step = (float)texture->height / wall_height;;
//      float tex_y = tex_y_off * tex_y_step;


   
//     int current_y = wall_start_top_y;
//     if(current_y < 0)
//     {
//         current_y = 0;
//         tex_y = abs(wall_start_top_y) * tex_y_step;
//     }

    

   
//    // shade_value = 1;

//     while (current_y < HEIGHT && current_y < wall_start_top_y + wall_height)
//     {
//         int tex_color = get_color_texture(texture, tex_x, tex_y);
//         ft_pixel_put(cub->image, wall_start_top_x, current_y, tex_color);
//         tex_y += tex_y_step;
//         current_y++;
//     }



//     if(cub->cast_result.current_ray_is_door)
//     {
//         texture = cub->door_texture;

//         if(cub->cast_result.is_vertical)
//         {
//             x_factor = hitY - ((int)(hitY / TILE_SIZE) * TILE_SIZE);
//             float tex_x_off = texture->width  - texture->width * cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
//             tex_x = (texture->width * x_factor) / TILE_SIZE;
//             tex_x -= tex_x_off;
//         }
//         else
//         {
//             x_factor = hitX - ((int)(hitX / TILE_SIZE) * TILE_SIZE);
//             float tex_x_off = texture->width  - texture->width * cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
//             tex_x = (texture->width * x_factor) / TILE_SIZE;
//             tex_x += tex_x_off;
//         }


//         tex_y_step = (float)texture->height / wall_height;
//         tex_y = tex_y_off * tex_y_step;
//         current_y = wall_start_top_y;
//         if(current_y < 0)
//         {
//             current_y = 0;
//             tex_y = abs(wall_start_top_y) * tex_y_step;
//         }


//         while (current_y < HEIGHT && current_y < wall_start_top_y + wall_height)
//         {
//             int tex_color = get_color_texture(texture, tex_x, tex_y);
//             ft_pixel_put(cub->image, wall_start_top_x, current_y, tex_color);
//             tex_y += tex_y_step;
//             current_y++;
//         }
//     }
// }

void render_door(t_cub3d *cub, t_cast_result *res, int wall_start_top_y, int wall_height)
{
    mlx_texture_t *texture = cub->door_texture;
    float x_factor = 0;
    float tex_x = 0;
    float hitX = res->inter.x;
    float hitY = res->inter.y;
    float tex_y_off = 0;
    float tex_y_step = (float)texture->height / wall_height;
    float tex_y = tex_y_off * tex_y_step;
    int current_y = wall_start_top_y;

    if(cub->cast_result.current_ray_is_door)
    {
        texture = cub->door_texture;

        if(cub->cast_result.is_vertical)
        {
            x_factor = hitY - ((int)(hitY / TILE_SIZE) * TILE_SIZE);
            float tex_x_off = texture->width  - texture->width * cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
            tex_x = (texture->width * x_factor) / TILE_SIZE;
            tex_x -= tex_x_off;
        }
        else
        {
            x_factor = hitX - ((int)(hitX / TILE_SIZE) * TILE_SIZE);
            float tex_x_off = texture->width  - texture->width * cub->door_infos[cub->cast_result.current_ray_door_index].close_factor;
            tex_x = (texture->width * x_factor) / TILE_SIZE;
            tex_x += tex_x_off;
        }


        tex_y_step = (float)texture->height / wall_height;
        tex_y = tex_y_off * tex_y_step;
        current_y = wall_start_top_y;
        if(current_y < 0)
        {
            current_y = 0;
            tex_y = abs(wall_start_top_y) * tex_y_step;
        }


        while (current_y < HEIGHT && current_y < wall_start_top_y + wall_height)
        {
            int tex_color = get_color_texture(texture, tex_x, tex_y);
            ft_pixel_put(cub->image, res->current_ray, current_y, tex_color);
            tex_y += tex_y_step;
            current_y++;
        }
    }
}

void build_wall_render_info(t_cub3d *cub, t_cast_result *res, t_wall_render_info *wr)
{
    float correct_dist;
    float distance_projection_plane;

    ft_bzero(wr, sizeof(t_wall_render_info));
    correct_dist = res->dist * cos(res->angle - cub->camera.dir);
    distance_projection_plane = (WIDTH / 2) / tanf(degree_to_radian(cub->camera.fov / 2));
    wr->wall_height = (TILE_SIZE / correct_dist)  *  distance_projection_plane;
    wr->wall_top = (HEIGHT /2 ) - ((int)wr->wall_height / 2);
    wr->hit_x = res->inter.x;
    wr->hit_y = res->inter.y;
}

void render_wall(t_cub3d *cub, t_cast_result *res)
{
    t_wall_render_info wr;
    float x_factor;



    build_wall_render_info(cub, res, &wr);
    if (res->is_vertical)
    {
        x_factor = wr.hit_y - ((int)(wr.hit_y / TILE_SIZE) * TILE_SIZE);
        if (cos(res->angle) >= 0)
        {
            wr.texture = cub->east_texture;
            wr.tex_x = (cub->east_texture->width * x_factor) / TILE_SIZE;
        }
        else 
        {
            x_factor = (cub->west_texture->width * x_factor) / TILE_SIZE;
            wr.tex_x = cub->west_texture->width - x_factor;
            wr.texture = cub->west_texture;
        }
    }
    else
    {
        x_factor = wr.hit_x - ((int)(wr.hit_x / TILE_SIZE) * TILE_SIZE);
        if(sin(res->angle) < 0)
        {
  
            wr.texture = cub->north_texture;
            wr.tex_x = (cub->north_texture->width * x_factor) / TILE_SIZE;
            
        }
        else 
        {
            x_factor = (cub->south_texture->width * x_factor) / TILE_SIZE;
            wr.tex_x = cub->south_texture->width - x_factor;
            wr.texture = cub->south_texture;
        }
    }

     wr.tex_y_step = (float)wr.texture->height / wr.wall_height;;

    int current_y = wr.wall_top;
    if(current_y < 0)
    {
        current_y = 0;
        wr.tex_y = abs((int)wr.wall_top) * wr.tex_y_step;
    }

    while (current_y < HEIGHT && current_y < wr.wall_top + wr.wall_height)
    {
        int tex_color = get_color_texture(wr.texture, wr.tex_x, wr.tex_y);
        ft_pixel_put(cub->image, res->current_ray, current_y, tex_color);
        wr.tex_y += wr.tex_y_step;
        current_y++;
    }
    render_door(cub, res, wr.wall_top, wr.wall_height);
}


t_direction get_direction(double angle)
{
    t_direction direction = {false, false, false, false};
    if (angle > 0 && angle < M_PI)
        direction.down = true;
    else
        direction.up = true;
    if (angle < M_PI_2 || angle > 3 * M_PI_2)
        direction.right = true;
    else
        direction.left = true;
    return direction;
}

void normalize_angle(double *angle)
{
    if (*angle < 0)
        *angle += 2 * M_PI;
    if (*angle > 2 * M_PI)
        *angle -= 2 * M_PI;
}

void init_cast_result(t_cast_result *cast_result, t_cast_request *request)
{
    ft_bzero(cast_result, sizeof(t_cast_result));
    cast_result->angle = request->angle;
    cast_result->current_ray = request->current_ray;
    cast_result->is_for_collision = request->is_for_collision;
    cast_result->direction = get_direction(request->angle);
}

void solve_v_intersections(t_cub3d *cub, t_map *map, t_cast_result *res)
{
    t_vec2 point;

    res->inter.x = floor(cub->camera.pos.x / TILE_SIZE) * TILE_SIZE;
    if (res->direction.right)
        res->inter.x += TILE_SIZE;
    res->inter.y = cub->camera.pos.y + (res->inter.x - cub->camera.pos.x) * tan(res->angle);
    res->xo = TILE_SIZE;
    if (res->direction.left)
        res->xo *= -1;
    res->yo = TILE_SIZE * tan(res->angle);
    if ((res->direction.up && res->yo > 0) || (res->direction.down && res->yo < 0))
        res->yo *= -1;
    while (true)
    {
        point.x = res->inter.x;
        point.y = res->inter.y;
        if (res->direction.left)
            point.x -= 1;
        if (is_solid_tile(point, map, cub, res))
            break;
        res->inter.x += res->xo;
        res->inter.y += res->yo;
    }
}

void solve_h_intersections(t_cub3d *cub, t_map *map, t_cast_result *res)
{
    t_vec2 point;

    res->inter.y = floor(cub->camera.pos.y / TILE_SIZE) * TILE_SIZE;
    if (res->direction.down)
        res->inter.y += TILE_SIZE;
    res->inter.x = cub->camera.pos.x + (res->inter.y - cub->camera.pos.y) / tan(res->angle);
    res->yo = TILE_SIZE;
    if (res->direction.up)
        res->yo *= -1;
    res->xo = TILE_SIZE / tan(res->angle);
    if ((res->direction.left && res->xo > 0) || (res->direction.right && res->xo < 0))
        res->xo *= -1;
    while (true)
    {
        point.x = res->inter.x;
        point.y = res->inter.y;
        if (res->direction.up)
            point.y -= 1;
        if (is_solid_tile(point, map, cub, res))
            break;
        res->inter.x += res->xo;
        res->inter.y += res->yo;
    }
}   

t_cast_result ray_cast_vertical(t_cub3d *cub, t_map *map, t_cast_request *request)
{;
    t_cast_result res;

    init_cast_result(&res, request);
    res.is_vertical = true;
    solve_v_intersections(cub, map, &res);
    res.dist = sqrt(pow(res.inter.x - cub->camera.pos.x, 2) + pow(res.inter.y - cub->camera.pos.y, 2));
    return res;
}

t_cast_result ray_cast_horizontal(t_cub3d *cub, t_map *map, t_cast_request *request)
{
    t_cast_result res;

    init_cast_result(&res, request);
    res.is_vertical = false;
    solve_h_intersections(cub, map, &res);
    res.dist = sqrt(pow(res.inter.x - cub->camera.pos.x, 2) + pow(res.inter.y - cub->camera.pos.y, 2));
    return res;
}

float ray_cast(t_cub3d *cub, t_map *map, t_cast_request *request)
{
    normalize_angle(&request->angle);
    t_cast_result v_res = ray_cast_vertical(cub, map, request);
    t_cast_result h_res = ray_cast_horizontal(cub, map, request);
    t_cast_result res;
    if (v_res.dist < h_res.dist)
        res = v_res;
    else
        res = h_res;
    cub->cast_result = res;
    if (cub->display_debug)
    {
        ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * cub->minimap_scale, cub->camera.pos.y * cub->minimap_scale}, 
            &(t_vec2){res.inter.x * cub->minimap_scale, res.inter.y * cub->minimap_scale}, request->color);
    }
    else
    {
        render_wall(cub, &res);
    }
    return res.dist;
}

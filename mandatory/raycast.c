#include "cub3d.h"

bool is_solid_tile(t_vec2 inter, t_vec2 *origin,  t_map *map, t_cub3d* cub, bool vetical_check, float ray_angle, float xo, float yo)
{
    int x = inter.x / TILE_SIZE;
    int y = inter.y / TILE_SIZE;

    (void)ray_angle;

    t_vec2 pushed_inter = {inter.x + (xo / 2), inter.y + (yo / 2)};

    if (x <= 0 || y <= 0 || x >= map->width - 1 || y >= map->height - 1)
        return true;
    if (map->addr[y][x] == '1' || map->addr[y][x] == 'V' || map->addr[y][x] == 'H')
    {
        if (map->addr[y][x] == 'V' || map->addr[y][x] == 'H') //NOTE : remove this for loop, use while
        {
            for (int i = 0; i < MAX_DOORS; i++)
            {
                if (cub->door_infos[i].map_x == x && cub->door_infos[i].map_y == y)
                {
                    if((vetical_check && !cub->door_infos[i].is_vertical) || (!vetical_check && cub->door_infos[i].is_vertical))
                        return false;
                    {
                        if(cub->door_infos[i].is_vertical)
                        {
                            float x_factor = pushed_inter.y - ((int)(pushed_inter.y / TILE_SIZE) * TILE_SIZE);
                            x_factor = (TILE_SIZE - x_factor) / TILE_SIZE;
                            if(x_factor > 1)
                                x_factor = 1;
                            if(x_factor > cub->door_infos[i].close_factor)
                                    return false;
                            *origin = pushed_inter;
                        }
                        else
                        {
                            float y_factor = pushed_inter.x - ((int)(pushed_inter.x / TILE_SIZE) * TILE_SIZE);
                            y_factor = y_factor / TILE_SIZE;
                            if(y_factor > cub->door_infos[i].close_factor)
                                    return false;  
                            *origin = pushed_inter;                     
                        }
                        cub->is_current_ray_door = true;
                        cub->current_ray_door_index = i;
                        break;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

t_vec2 solve_h_intersections(t_cub3d *cub, t_map *map, double angle, t_direction direction)
{
    t_vec2 inter;
    float xo;
    float yo;
   
   inter.y = floor(cub->camera.pos.y / TILE_SIZE) * TILE_SIZE;
   if(direction.down)
     inter.y += TILE_SIZE;
    inter.x = cub->camera.pos.x + (inter.y - cub->camera.pos.y) / tan(angle);
    yo = TILE_SIZE;
    if(direction.up)
      yo *= -1;
    xo = TILE_SIZE / tan(angle);
    if((direction.left && xo > 0) || (direction.right && xo < 0))
      xo *= -1;
    while (true)
    {
        t_vec2 point = {inter.x, inter.y};
        if(direction.up)
            point.y -= 1;
        if (is_solid_tile(point, &inter, map, cub, false, angle, xo, yo))
            break;
        inter.x += xo;
        inter.y += yo;
    }
    return inter;
}

t_vec2 solve_v_intersections(t_cub3d *cub, t_map *map, double dir, t_direction direction)
{
    t_vec2 inter;
    float xo;
    float yo; 

    inter.x = floor(cub->camera.pos.x / TILE_SIZE) * TILE_SIZE;
    if (direction.right)
        inter.x += TILE_SIZE;
    inter.y = cub->camera.pos.y + (inter.x - cub->camera.pos.x) * tan(dir);
    xo = TILE_SIZE;
    if (direction.left)
        xo *= -1;
    yo = TILE_SIZE * tan(dir);
    if ((direction.up && yo > 0) || (direction.down && yo < 0))
        yo *= -1;
    while (true)
    {
        t_vec2 point = {inter.x, inter.y};
        if (direction.left)
            point.x -= 1;
        if (is_solid_tile(point, &inter, map, cub, true, dir, xo, yo))
            break;
        inter.x += xo;
        inter.y += yo;
    }
    return inter;
}


void render_wall(t_cub3d *cub, double dist, double ray_angle, bool is_vertical, int current_ray, float hitX, float hitY)
{
    dist = dist * cos(ray_angle - cub->camera.dir);
    float distance_projection_plane = (WIDTH / 2) / tanf(degree_to_radian(cub->camera.fov / 2));
    double wall_height = (TILE_SIZE / dist)  *  distance_projection_plane;


  
   
    int wall_start_top_y = (HEIGHT /2 ) - ((int)wall_height / 2);
    int wall_start_top_x = current_ray;;

    float x_factor = 0;
    float tex_x = 0;

    mlx_texture_t *texture = NULL;

    if (is_vertical)
    {
        //if down
        x_factor = hitY - ((int)(hitY / TILE_SIZE) * TILE_SIZE);
        if (cos(ray_angle) >= 0)
        {
 
            texture = cub->east_texture;
            tex_x = (cub->east_texture->width * x_factor) / TILE_SIZE;

        }
        else 
        {
            x_factor = (cub->west_texture->width * x_factor) / TILE_SIZE;
            tex_x = cub->west_texture->width - x_factor;
            texture = cub->west_texture;
            
        }

      
    }
    else
    {
        x_factor = hitX - ((int)(hitX / TILE_SIZE) * TILE_SIZE);
        if(sin(ray_angle) < 0)
        {
  
            texture = cub->north_texture;
            tex_x = (cub->north_texture->width * x_factor) / TILE_SIZE;
            
        }
        else 
        {
 
            x_factor = (cub->south_texture->width * x_factor) / TILE_SIZE;
            tex_x = cub->south_texture->width - x_factor;
            texture = cub->south_texture;
            
        }


    }



    float tex_y_off = 0;   
    float tex_y_step = (float)texture->height / wall_height;;
     float tex_y = tex_y_off * tex_y_step;


   
    int current_y = wall_start_top_y;
    if(current_y < 0)
    {
        current_y = 0;
        tex_y = abs(wall_start_top_y) * tex_y_step;
    }

    

   
   // shade_value = 1;

    while (current_y < HEIGHT && current_y < wall_start_top_y + wall_height)
    {
        int tex_color = get_color_texture(texture, tex_x, tex_y);
        ft_pixel_put(cub->image, wall_start_top_x, current_y, tex_color);
        tex_y += tex_y_step;
        current_y++;
    }



    if(cub->is_current_ray_door)
    {
        texture = cub->door_texture;
        x_factor = hitY - ((int)(hitY / TILE_SIZE) * TILE_SIZE);
        tex_x = (texture->width * x_factor) / TILE_SIZE;

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
            ft_pixel_put(cub->image, wall_start_top_x, current_y, tex_color);
            tex_y += tex_y_step;
            current_y++;
        }
    }
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




int ray_cast(t_cub3d *cub, t_map *map, double angle, int color, int current_ray)
{

    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
    cub->is_current_ray_door = false;
    bool is_h_ray_door = false;
    bool is_v_ray_door = false;

    int door_h_index = -1;
    int door_v_index = -1;

    t_vec2 h_inter = solve_h_intersections(cub, map, angle , get_direction(angle));
    is_h_ray_door = cub->is_current_ray_door;
    door_h_index = cub->current_ray_door_index;
    cub->is_current_ray_door = false;
    cub->current_ray_door_index = -1;
    t_vec2 v_inter = solve_v_intersections(cub, map, angle, get_direction(angle));
    is_v_ray_door = cub->is_current_ray_door;
    door_v_index = cub->current_ray_door_index;
    t_vec2 inter;

    // lets calculate the distance between the player and the intersection
    float v_dist = sqrt(pow(v_inter.x - cub->camera.pos.x, 2) + pow(v_inter.y - cub->camera.pos.y, 2));
    float h_dist = sqrt(pow(h_inter.x - cub->camera.pos.x, 2) + pow(h_inter.y - cub->camera.pos.y, 2));

    if (v_dist < h_dist)
    {
        inter = v_inter;
        cub->is_current_ray_door = is_v_ray_door;
        cub->current_ray_door_index = door_v_index;
    }
       
    else
    {
        inter = h_inter;
        cub->is_current_ray_door = is_h_ray_door;
        cub->current_ray_door_index = door_h_index;
    }

    float dist = sqrt(pow(inter.x - cub->camera.pos.x, 2) + pow(inter.y - cub->camera.pos.y, 2));
    if (cub->display_debug)
    {
            ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * cub->minimap_scale, cub->camera.pos.y * cub->minimap_scale}, 
            &(t_vec2){inter.x * cub->minimap_scale, inter.y * cub->minimap_scale}, color);
    }
    else
    {
        render_wall(cub, dist, angle, v_dist < h_dist,  current_ray, inter.x, inter.y);
    }

    return dist;
}

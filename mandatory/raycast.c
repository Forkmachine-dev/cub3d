#include "cub3d.h"

bool is_solid_tile(t_vec2 inter, t_map *map)
{
    int x = inter.x / TILE_SIZE;
    int y = inter.y / TILE_SIZE;

    if (x <= 0 || y <= 0 || x >= map->width - 1 || y >= map->height - 1)
        return true;
    if (map->addr[y][x] == '1')
        return true;
    return false;
}

int point_inside_fov(float camera_angle, float fov, t_vec2 camera, t_vec2 point) {
    float angle_to_point = atan2f(point.y - camera.y, point.x - camera.x) * 180.0 / M_PI;
    float angle_difference = fabsf(angle_to_point - camera_angle);
    
    // Ensure the angle is within [0, 360] degrees
    angle_difference = fminf(angle_difference, 360.0f - angle_difference);
    
    // Check if the angle to the point is within the FOV angle range
    return angle_difference <= fov / 2.0f;
}

t_vec2 solve_h_intersections(t_camera *camera, t_map *map, double dir)
{
    t_vec2 inter;

    float atan = -1 / tan(dir);
    float xo, yo;
   
   // float dof = 0;
    
    bool dir_up = false;
    if(dir > M_PI) // looking up
    {
        inter.y = ((int)camera->pos.y / TILE_SIZE) * TILE_SIZE;
        inter.x = camera->pos.x + (camera->pos.y - inter.y) * atan;
        yo = -TILE_SIZE;
        xo = -yo * atan;
        dir_up = true;
    }
    else
    {
        inter.y = ((int)camera->pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        inter.x = camera->pos.x + (camera->pos.y - inter.y) * atan;
        yo = TILE_SIZE;
        xo = -yo * atan;
    }


    while (true)
    {
        t_vec2 point = {inter.x, inter.y};
        if(dir_up)
            point.y -= 1;
        if (is_solid_tile(point, map))
            break;
        inter.x += xo;
        inter.y += yo;
        //dof += 1;
    }

    return inter;
}

t_vec2 solve_v_intersections(t_camera *camera, t_map *map, double dir)
{
    t_vec2 inter;

    float natan = -tan(dir);
    float xo, yo;
    //float dof = 0;
    bool dir_left = false;
    if (dir > M_PI_2 && dir < 3 * M_PI_2) // looking left
    {
        inter.x = ((int)camera->pos.x / TILE_SIZE) * TILE_SIZE;
        inter.y = camera->pos.y + (camera->pos.x - inter.x) * natan;
        xo = -TILE_SIZE;
        yo = -xo * natan;
        dir_left = true;
    }
    else // looking right
    {
        inter.x = ((int)camera->pos.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        inter.y = camera->pos.y + (camera->pos.x - inter.x) * natan;
        xo = TILE_SIZE;
        yo = -xo * natan;
    }
    
    while (true)
    {
        t_vec2 point = {inter.x, inter.y};
        if(dir_left)
            point.x -= 1;
        if (is_solid_tile(point, map))
            break;
        inter.x += xo;
        inter.y += yo;
        //dof += 1;
    }

    return inter;
}
void render_wall(t_cub3d *cub, double dist, double ray_angle, bool is_vertical, int current_ray)
{

    //first, lets fix the fisheye effect
    double angle = cub->camera.dir - ray_angle;
    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
    dist = dist * cos(angle);
    float distance_projection_plane = (WIDTH / 2) / tan(degree_to_radian(cub->camera.fov) / 2);
    double wall_height = (TILE_SIZE / dist)  *  distance_projection_plane;
    // we need to take into account the TILE_SIZE
    if(wall_height > HEIGHT)
        wall_height = HEIGHT;
    
    int wall_start_top_y = (HEIGHT - wall_height) / 2;
    int wall_start_top_x = current_ray;
    int wall_end_bottom_y = wall_start_top_y + wall_height;

    int color = 0xFF000080;
    if(is_vertical) // MAKE IT A BIT DARKER
        color = 0xFF000060;
    ft_draw_line(cub, &(t_vec2){wall_start_top_x, wall_start_top_y}, &(t_vec2){wall_start_top_x, wall_end_bottom_y}, color);
}

int ray_cast(t_cub3d *cub, t_map *map, double angle, bool debug, int color, int current_ray)
{

    if(angle < 0)
        angle += 2 * M_PI;
    if(angle > 2 * M_PI)
        angle -= 2 * M_PI;
    // vertical intersection
    t_vec2 h_inter = solve_h_intersections(&cub->camera, map, angle);
    t_vec2 v_inter = solve_v_intersections(&cub->camera, map, angle);
    t_vec2 inter;
    // we will do horizontal intersection in a bit, first lets visualize the vertical intersection

    debug = false;

    // lets calculate the distance between the player and the intersection
    float v_dist = sqrt(pow(v_inter.x - cub->camera.pos.x, 2) + pow(v_inter.y - cub->camera.pos.y, 2));
    float h_dist = sqrt(pow(h_inter.x - cub->camera.pos.x, 2) + pow(h_inter.y - cub->camera.pos.y, 2));

    if (v_dist < h_dist)
        inter = v_inter;
    else
        inter = h_inter;
    float dist = sqrt(pow(inter.x - cub->camera.pos.x, 2) + pow(inter.y - cub->camera.pos.y, 2));
    if (debug)
    {
            ft_draw_line(cub, &(t_vec2){cub->camera.pos.x * ZOOM, cub->camera.pos.y * ZOOM}, 
            &(t_vec2){inter.x * ZOOM, inter.y * ZOOM}, color);
    }
    else
    {
        render_wall(cub, dist, angle, v_dist < h_dist,  current_ray);
    }

    return dist;
}
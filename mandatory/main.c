#include "cub3d.h"

void execute_cub3d(t_cub3d *cub)
{
    mlx_loop(cub->mlx);
}

void fake_map(t_cub3d *cub)
{
    // now we dont have a map parser, so we will just assume we have a map
    //we need to malloc a 2d array of chars [20][10]
    //we will fill it with 0s and 1s
    // we will use the next map
    // 11111111111111111111
    // 10000000000000000001
    // 10011111000001100001
    // 10000000000001111101
    // 11111111000000000001
    // 10000000000000000001
    // 10000000000000000001
    // 11110000000000000001
    // 10000000000000000001
    // 11111111111111111111


    cub->map.width = 20;
    cub->map.height = 10;

    cub->map.addr = malloc(sizeof(char *) * cub->map.height);

    cub->map.addr[0] = "11111111111111111111";
    cub->map.addr[1] = "10000000000000000001";
    cub->map.addr[2] = "10011111000001100001";
    cub->map.addr[3] = "10000000000001111101";
    cub->map.addr[4] = "11111111000000000001";
    cub->map.addr[5] = "10000000000000000001";
    cub->map.addr[6] = "10000000000000000001";
    cub->map.addr[7] = "11110000000000000001";
    cub->map.addr[8] = "100000000N0000000001";
    cub->map.addr[9] = "11111111111111111111";

    // search for the player position
    for (int y = 0; y < cub->map.height; y++)
    {
        for (int x = 0; x < cub->map.width; x++)
        {
            if (cub->map.addr[y][x] == 'N')
            {
                cub->camera.pos.x = x;
                cub->camera.pos.y = y;
                cub->camera.dir = degree_to_radian(270);
                cub->camera.fov = 60;
                return;
            }
        }
    }
}

int		main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    t_cub3d cub;

    // [TODO] Parse the map
    // [TODO] Error handling
    if (init_cub3d(&cub) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    fake_map(&cub);
    execute_cub3d(&cub);
    terminate_cub3d(&cub);
    return (0);
}

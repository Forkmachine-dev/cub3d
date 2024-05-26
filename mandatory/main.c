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

    // map 2
    //        1111111111111111111111111111111111111100000000000
    //        10000000001100000000000000000000000001
    //        10110000011100000111000011111111111101
    //        1001000000000000010000001          101
    //111111111011000001110000010000001          101
    //1000000000110000011101111111111001         101
    //11110111111 11011100000000001  100111111111101
    //11110111  1111011101010010001   10000000000001
    //11000000110101011100000010001    1001111111101
    //100000000000000011000000100011111110111111110111111
    //100000000000000011010100100000000000000000000000001
    //11000001110101011111011110N011111111111111111111101
    //  110111 1110101 101111010001                   101
    // 1110111 1111111 1111111111111111111111111111111101
    //1000000010000000100000000000000000000000011000000011111
    //11111100001111100011011011111111011111110100111110000001
    //       1011     111 101101      101      1001     1111101
    //       1001        101 101      1011111110011111111111101
    //        100111111110111101111111101111110000000000001 101
    //         100000000000000000000000000000000111110111011001
    //          1000000000000000000000000000000000000000000001
    //           11011111111110110111110101111111111111011111
    //           1100000000000011000000010000000000000001
    //            11111111111111111111111111111111111111

    cub->map.width = 57;
    cub->map.height = 24;

    cub->map.addr = malloc(sizeof(char *) * cub->map.height);

    // cub->map.addr[0] = "11111111111111111111";
    // cub->map.addr[1] = "10000000000000000001";
    // cub->map.addr[2] = "10011111000001100001";
    // cub->map.addr[3] = "10000000000001011101";
    // cub->map.addr[4] = "11111111000000000001";
    // cub->map.addr[5] = "10000000000000000001";
    // cub->map.addr[6] = "10000000000000000001";
    // cub->map.addr[7] = "11110000000000000001";
    // cub->map.addr[8] = "100000000N0000000001";
    // cub->map.addr[9] = "11111111111111111111";

    cub->map.addr[0] =  "        11111111111111111111111111111111111111           ";
    cub->map.addr[1] =  "        10000000001100000000000000000000000001           ";
    cub->map.addr[2] =  "        10110000011100000111000011111111111101           ";
    cub->map.addr[3] =  "        1001000000000000010000001          101           ";
    cub->map.addr[4] =  "111111111011000001110000010000001          101           ";
    cub->map.addr[5] =  "10000000001100000111011111H1111001         101           ";
    cub->map.addr[6] =  "11110111111 110111000000V000V  100111111111101           ";
    cub->map.addr[7] =  "11110111  1111011101010010001   10000000000001           ";
    cub->map.addr[8] =  "11000000110101011100000010001    1001111111101           ";
    cub->map.addr[9] =  "100000000000000011000000100011111110111111110111111      ";
    cub->map.addr[10]=  "100000000000000011010100100000000000000000000000001      ";
    cub->map.addr[11]=  "11000001110101011111011110N111111111111111111111101      ";
    cub->map.addr[12]=  "  110111 1110101 101111010001                   101      ";
    cub->map.addr[13]=  " 1110111 1111111 1111111111111111111111111111111101      ";
    cub->map.addr[14]=  "1000000010000000100000000000000000000000011000000011111  ";
    cub->map.addr[15]=  "11111110001111100011011011111111011111110100111110000001 ";
    cub->map.addr[16]=  "       1011     111 101101      101      1001     1111101";
    cub->map.addr[17]=  "       1001        101 101      1011111110011111111111101";
    cub->map.addr[18]=  "        100111111110111101111111101111110000000000001 101";
    cub->map.addr[19]=  "         100000000000000000000000000000000111110111011001";
    cub->map.addr[20]=  "          1000000000000000000000000000000000000000000001 ";
    cub->map.addr[21]=  "           11011111111110110111110101111111111111011111  ";
    cub->map.addr[22]=  "           1100000000000011000000010000000000000001      ";
    cub->map.addr[23]=  "           1111111111111111111111111111111111111111      ";
        


    

    double initial_mini_map_scale = 1;
    int width_pixel_count_for_initail_scale = cub->map.width * TILE_SIZE * initial_mini_map_scale;
    int height_pixel_count_for_initail_scale = cub->map.height * TILE_SIZE * initial_mini_map_scale;

   if (width_pixel_count_for_initail_scale > height_pixel_count_for_initail_scale)
        cub->minimap_scale = ((double)WIDTH) / width_pixel_count_for_initail_scale;
    else
        cub->minimap_scale = ((double)HEIGHT) / height_pixel_count_for_initail_scale;
    printf("minimap scale %f\n", cub->minimap_scale);

    // search for the player position
    int current_door = 0;
    ft_bzero(cub->door_infos, sizeof(t_door_info) * MAX_DOORS);
    int x = 0;
    int y = 0;

    while (y < cub->map.height)
    {
        x = 0;
        while(x < cub->map.width)
        {
            if (cub->map.addr[y][x] == 'N')
            {

                cub->camera.pos.x = x * TILE_SIZE + TILE_SIZE / 2;
                cub->camera.pos.y = y * TILE_SIZE + TILE_SIZE / 2;
                cub->camera.dir = degree_to_radian(270);
                cub->camera.fov = 60;
            }
            else if (cub->map.addr[y][x] == 'V' || cub->map.addr[y][x] == 'H')
            {
                if(current_door >= MAX_DOORS)
                {
                    printf("Max doors reached, Inocrrect map\n");
                    return;
                }
                t_door_info door_info;
                door_info.map_x = x;
                door_info.map_y = y;
                door_info.close_factor = 1;
                door_info.is_opening = false;
                door_info.is_vertical = cub->map.addr[y][x] == 'V';
                cub->door_infos[current_door] = door_info;
                current_door++;
            }
         x++;
        }
       
        y++;
    

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

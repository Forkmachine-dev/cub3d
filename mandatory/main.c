/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:29:01 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:29:02 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	execute_cub3d(t_cub3d *cub)
{
	mlx_loop(cub->mlx);
}

int	cub_3d(int argc, char **argv)
{
	t_cub3d	cub;

	ft_bzero(&cub, sizeof(t_cub3d));
	if (parse_map(&cub, argc, argv) == EXIT_FAILURE)
	{
		terminate_cub3d(&cub);
		return (EXIT_FAILURE);
	}
	if (init_cub3d(&cub) == EXIT_FAILURE)
	{
		terminate_cub3d(&cub);
		return (EXIT_FAILURE);
	}
	execute_cub3d(&cub);
	terminate_cub3d(&cub);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int	ret;

	ret = cub_3d(argc, argv);
	system("leaks cub3D");
	return (ret);
}

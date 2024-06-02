/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 01:28:34 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/02 01:28:37 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	terminate_cub3d(t_cub3d *cub)
{
	if (cub->mlx)
		mlx_close_window(cub->mlx);
	if (cub->image)
		mlx_delete_image(cub->mlx, cub->image);
	free_cub(cub);
	ft_bzero(cub, sizeof(t_cub3d));
	return (EXIT_SUCCESS);
}

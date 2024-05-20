/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 20:15:47 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/05/20 20:15:50 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_fmax(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

int	abs(int a)
{
	if (a < 1)
		return (a * -1);
	return (a);
}

double	degree_to_radian(double angle_degrees)
{
	double	angle_radians;

	angle_radians = angle_degrees * (M_PI / 180.0f);
	return (angle_radians);
}
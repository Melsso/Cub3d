/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:10:47 by smallem           #+#    #+#             */
/*   Updated: 2023/12/14 19:43:48 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	load_images(t_cub *data)
// {
// 	int			fd;
// 	mlx_image_t	*img;

// 	fd = open(data->nop, O_RDONLY);
// 	if (fd < 0)
// 		ft_error("Error\nCould not open image!", data, NULL, 1);
// }

float	degToRad(int a)
{
	return (a * M_PI / 180.0);
}

int fixAng(int a)
{ 
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360; 
	return (a);
}
float distance(int ax, int ay, int bx, int by, int ang)
{ 
	return (cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay));
}

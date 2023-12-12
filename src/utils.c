/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:10:47 by smallem           #+#    #+#             */
/*   Updated: 2023/12/12 18:18:16 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	load_images(t_cub *data)
{
	int			fd;
	mlx_image_t	*img;

	fd = open(data->nop, O_RDONLY);
	if (fd < 0)
		ft_error("Error\nCould not open image!", data, NULL, 1);
}

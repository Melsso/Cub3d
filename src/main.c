/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:56:43 by smallem           #+#    #+#             */
/*   Updated: 2023/12/15 19:20:04 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	data;
	int		x;
	int		y;

	if (argc != 2)
	{
		printf("Invalid number of arguments!\n");
		exit(1);
	}
	read_content(&data, argv);
	y = -1;
	while (data.map[++y])
	{
		x = -1;
		while (data.map[y][++x])
		{
			if (data.map[y][x] == 'N' || data.map[y][x] == 'S'
				|| data.map[y][x] == 'W' || data.map[y][x] == 'E')
			{
				data.p.x = x;
				data.p.y = y;
				data.cam_dir = data.map[y][x];
				break ;
			}
		}
	}
	init(&data);
	// load_images(&data);
}

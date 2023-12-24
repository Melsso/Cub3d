/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:56:43 by smallem           #+#    #+#             */
/*   Updated: 2023/12/24 14:30:13 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	data;

	if (argc != 2)
	{
		printf("Invalid number of arguments!\n");
		exit(1);
	}

	read_content(&data, argv);

	init(&data);
	if (!mlx_loop_hook(data.win, events, &data))
		ft_error("Error\nLoopHook mlx error!", &data, NULL, 1);
	mlx_loop(data.win);
	ft_error(NULL, &data, NULL, 1);
	return (0);
}

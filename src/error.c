/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:09:17 by smallem           #+#    #+#             */
/*   Updated: 2023/12/26 13:11:19 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **mat)
{
	int	i;

	if (!mat)
		return ;
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i++] = NULL;
	}
	mat = NULL;
}

void	call_err(char *msg, t_cub *data, char **mat, char **m)
{
	free_split(m);
	ft_error(msg, data, mat, 1);
}

void	ft_error(char *msg, t_cub *data, char **mat, int flag)
{
	int	i;

	if (flag)
	{
		i = -1;
		while (++i < 4)
			if (data->tex[i])
				mlx_delete_texture(data->tex[i]);
		if (data->img)
			mlx_delete_image(data->win, data->img);
		mlx_terminate(data->win);
	}
	if (msg)
		printf("%s\n", msg);
	if (mat)
		free_split(mat);
	exit(1);
}

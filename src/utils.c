/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:10:47 by smallem           #+#    #+#             */
/*   Updated: 2024/01/10 16:55:29 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int32_t	col(int32_t r, int32_t g, int32_t b)
{
	return (r << 24 | g << 16 | b << 8 | 0x000000FF);
}

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
	int	ex_stat;

	ex_stat = 0;
	if (flag)
	{
		i = -1;
		while (++i < 4)
			if (data->tex[i])
				mlx_delete_texture(data->tex[i]);
		if (data->img)
			mlx_delete_image(data->win, data->img);
		if (data->win)
			mlx_terminate(data->win);
	}
	if (msg)
	{
		printf("%s\n", msg);
		ex_stat = 1;
	}
	if (mat)
		free_split(mat);
	exit(ex_stat);
}

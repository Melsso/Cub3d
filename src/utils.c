/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:10:47 by smallem           #+#    #+#             */
/*   Updated: 2024/01/11 13:10:49 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**cp_map(t_cub *data)
{
	int		i;
	char	**map;

	i = -1;
	while (data->map[++i])
		;
	map = (char **)malloc(sizeof(char *) * i);
	if (!map)
		ft_error("Error\nMalloc error!", data, NULL, 0);
	i = -1;
	while (data->map[++i])
	{
		map[i] = ft_strdup(data->map[i]);
		if (!map[i])
			ft_error("Error\nMalloc error!", data, map, 0);
	}
	map[i] = NULL;
	return (map);
}

int	is_pos(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
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

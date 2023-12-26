/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:47:30 by smallem           #+#    #+#             */
/*   Updated: 2023/12/26 15:11:28 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_vec(char c, t_cub *data)
{
	int	sign;

	sign = 1;
	if (c == 'S' || c == 'E')
		sign *= -1;
	if (c == 'N' || c == 'S')
	{
		data->vecs[1] = (t_vec2){0, 1 * -sign, 0, 0};
		data->vecs[2] = (t_vec2){FOV * sign, 0, 0, 0};
	}
	else
	{
		data->vecs[1] = (t_vec2){-1 * sign, 0, 0, 0};
		data->vecs[2] = (t_vec2){0, FOV * -sign, 0, 0};
	}
}

void	get_data(t_cub *data)
{
	int	i;
	int	j;

	i = -1;
	data->w = 0;
	while (data->map[++i])
	{
		if (ft_strlen(data->map[i]) > data->w)
			data->w = ft_strlen(data->map[i]);
		j = -1;
		while (data->map[i][++j])
		{
			if (is_pos(data->map[i][j]))
			{
				data->vecs[0].x = (double)j + 0.5;
				data->vecs[0].y = (double)i + 0.5;
				set_vec(data->map[i][j], data);
				data->map[i][j] = '0';
			}
		}
	}
	data->h = i;
}

void	init(t_cub *data)
{
	get_data(data);
	data->win = NULL;
	data->win = mlx_init(1920, 1080, "Cub3d", false);
	if (!data->win)
		ft_error("Error\nMlx_init failure!", data, NULL, 1);
	data->img = mlx_new_image(data->win, 1920, 1080);
	if (!data->img)
		ft_error("Error\nCould not create image!", data, NULL, 1);
	if (mlx_image_to_window(data->win, data->img, 0, 0) == -1)
		ft_error("Error\nImg2Win mlx failure!", data, NULL, 1);
}

void	rotate_camera(t_cub *data, int dir)
{
	short	sign;
	t_vec2	ang;

	if (dir == 2)
		sign = -1;
	else
		sign = 1;
	ang = (t_vec2){cos(ROT * sign), sin(ROT * sign), 0, 0};
	data->vecs[1].x = (data->vecs[1].x * ang.x) - (data->vecs[1].y * ang.y);
	data->vecs[1].y = (data->vecs[1].x * ang.y) + (data->vecs[1].y * ang.x);
	data->vecs[2].x = (data->vecs[2].x * ang.x) - (data->vecs[2].y * ang.y);
	data->vecs[2].y = (data->vecs[2].x * ang.y) + (data->vecs[2].y * ang.x);
}

void	movement(t_cub *data, int dir)
{
	t_vec2	v;
	t_vec2	p;

	p = (t_vec2){data->vecs[0].x, data->vecs[0].y};
	v = (t_vec2){data->vecs[1].x * MV, data->vecs[1].y * MV, 0, 0};
	if (dir == 1 && data->map[(int)(p.y + v.y)][(int)(p.x + v.x)] != '1')
		data->vecs[0] = (t_vec2){p.x + v.x, p.y + v.y};
	else if (dir == 2 && data->map[(int)(p.y - v.y)][(int)(p.x - v.x)] != '1')
		data->vecs[0] = (t_vec2){p.x - v.x, p.y - v.y};
	else if (dir == 3 && data->map[(int)(p.y - v.x)][(int)(p.x + v.y)] != '1')
		data->vecs[0] = (t_vec2){p.x + v.y, p.y - v.x};
	else if (dir == 4 && data->map[(int)(p.y + v.x)][(int)(p.x - v.y)] != '1')
		data->vecs[0] = (t_vec2){p.x - v.y, p.y + v.x};
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:53:55 by smallem           #+#    #+#             */
/*   Updated: 2023/12/26 15:13:28 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	raycast(t_cub *data, t_ray *ray)
{
	short		x;
	uint32_t	w;
	t_vec2		dist;
	t_vec2		vecs[3];

	x = -1;
	w = data->img->width;
	while (++x < (short)w)
	{
		get_info(data, ray, x, &dist);
		fix_ray(data, ray, &vecs, &dist);
		launch_ray(data, ray, &dist, &vecs);
		if (ray->axis == 'X')
		{
			ray->distance = vecs[1].x - dist.x;
			ray->hit = vecs[2].xi;
		}
		else
		{
			ray->distance = vecs[1].y - dist.y;
			ray->hit = vecs[2].yi;
		}
		render_walls(ray, x, data);
	}
}

void	paint(t_cub *data)
{
	unsigned short	x;
	unsigned short	y;
	int32_t			cols[2];
	uint32_t		w;
	uint32_t		h;

	cols[0] = col(data->cols[0].x, data->cols[0].y, data->cols[0].z);
	cols[1] = col(data->cols[1].x, data->cols[1].y, data->cols[1].z);
	x = -1;
	w = data->img->width;
	h = data->img->height;
	while (++x < w)
	{
		y = 0;
		while (y < h / 2)
			mlx_put_pixel(data->img, x, y++, cols[1]);
		while (y < h)
			mlx_put_pixel(data->img, x, y++, cols[0]);
	}
}

void	events(void *param)
{
	t_cub	*data;
	t_ray	ray;

	data = param;
	paint(data);
	raycast(data, &ray);
	if (mlx_is_key_down(data->win, MLX_KEY_ESCAPE))
		ft_error(NULL, data, NULL, 1);
	else if (mlx_is_key_down(data->win, MLX_KEY_W))
		movement(data, 1);
	else if (mlx_is_key_down(data->win, MLX_KEY_S))
		movement(data, 2);
	else if (mlx_is_key_down(data->win, MLX_KEY_A))
		movement(data, 3);
	else if (mlx_is_key_down(data->win, MLX_KEY_D))
		movement(data, 4);
	else if (mlx_is_key_down(data->win, MLX_KEY_RIGHT))
		rotate_camera(data, 1);
	else if (mlx_is_key_down(data->win, MLX_KEY_LEFT))
		rotate_camera(data, 2);
}

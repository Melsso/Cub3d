/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:05:06 by smallem           #+#    #+#             */
/*   Updated: 2023/12/26 15:08:53 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_info(t_cub *data, t_ray *ray, short x, t_vec2 *dist)
{
	double	cam_x;

	cam_x = (2 * x / (double)data->img->width - 1);
	ray->dir = (t_vec2){data->vecs[1].x + (data->vecs[2].x * cam_x),
		data->vecs[1].y + (data->vecs[2].y * cam_x), 0, 0};
	if (ray->dir.x)
		dist->x = fabs(1 / ray->dir.x);
	else
		dist->x = INFINITY;
	if (ray->dir.y)
		dist->y = fabs(1 / ray->dir.y);
	else
		dist->y = INFINITY;
	ray->pos = (t_vec2){0, 0, data->vecs[0].x, data->vecs[0].y};
}

void	fix_ray(t_cub *data, t_ray *ray, t_vec2 (*vecs)[3], t_vec2 *dist)
{
	if (ray->dir.y < 0)
	{
		vecs[0][0].yi = -1;
		vecs[0][1].y = (data->vecs[0].y - ray->pos.yi) * dist->y;
		vecs[0][2].yi = 0;
	}
	else
	{
		vecs[0][0].yi = 1;
		vecs[0][1].y = (ray->pos.yi + 1.0 - data->vecs[0].y) * dist->y;
		vecs[0][2].yi = 1;
	}
	if (ray->dir.x >= 0)
	{
		vecs[0][0].xi = 1;
		vecs[0][1].x = (ray->pos.xi + 1.0 - data->vecs[0].x) * dist->x;
		vecs[0][2].xi = 2;
	}
	else
	{
		vecs[0][0].xi = -1;
		vecs[0][1].x = (data->vecs[0].x - ray->pos.xi) * dist->x;
		vecs[0][2].xi = 3;
	}
}

void	launch_ray(t_cub *data, t_ray *ray, t_vec2 *dist, t_vec2 (*vecs)[3])
{
	while (1)
	{
		if (vecs[0][1].x < vecs[0][1].y)
		{
			vecs[0][1].x += dist->x;
			ray->pos.xi += vecs[0][0].xi;
			ray->axis = 'X';
		}
		else
		{
			vecs[0][1].y += dist->y;
			ray->pos.yi += vecs[0][0].yi;
			ray->axis = 'Y';
		}
		if (data->map[ray->pos.yi][ray->pos.xi] == '1')
			break ;
	}
}

void	get_tex_info(t_vec2 (*v)[3], t_ray *ray, t_cub *data)
{
	int			l_h;
	double		wx;
	uint32_t	h;
	char		c;

	h = data->img->height;
	l_h = (h) / ray->distance;
	c = ray->axis;
	v[0][0] = (t_vec2){0, 0, (h / 2) - (l_h / 2), (h / 2) + (l_h / 2)};
	if (v[0][0].xi < 0)
		v[0][0].xi = 0;
	if (v[0][0].yi >= (int)h)
		v[0][0].yi = h - 1;
	if (c == 'X')
		wx = data->vecs[0].y + (ray->distance * ray->dir.y);
	else
		wx = data->vecs[0].x + (ray->distance * ray->dir.x);
	wx -= floor(wx);
	v[0][2].xi = (int)(wx * (double)data->tex[ray->hit]->width);
	if ((c == 'X' && ray->dir.x > 0) || (c == 'Y' && ray->dir.y < 0))
		v[0][2].xi = data->tex[ray->hit]->width - v[0][2].xi - 1;
	v[0][1].y = (double)(data->tex[ray->hit]->height) / l_h;
	v[0][1].x = (v[0][0].xi - (h / 2) + (l_h / 2)) * v[0][1].y;
}

void	render_walls(t_ray *ray, short x, t_cub *data)
{
	t_vec2			v[3];
	int32_t			pxl;

	get_tex_info(&v, ray, data);
	while (v[0].xi < v[0].yi)
	{
		v[2].yi = v[1].x;
		pxl = (v[2].yi * data->tex[ray->hit]->width + v[2].xi) * 4;
		mlx_put_pixel(data->img, x, v[0].xi, col(data->tex[ray->hit]->pixels[pxl
				+ 0], data->tex[ray->hit]->pixels[pxl + 1],
				data->tex[ray->hit]->pixels[pxl + 2]));
		v[1].x += v[1].y;
		v[0].xi++;
	}
}

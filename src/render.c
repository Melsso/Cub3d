/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:53:55 by smallem           #+#    #+#             */
/*   Updated: 2023/12/24 17:19:03 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_camera(t_cub *data, int dir)
{
	double	cos_a;
	double	sin_a;

	if (dir == 1)
	{
		cos_a = cos(ROT);
		sin_a = sin(ROT);
	}
	else if (dir == 2)
	{	
		cos_a = cos(ROT * -1);
		sin_a = sin(ROT * -1);
	}
	data->vecs[1].x = (data->vecs[1].x * cos_a) - (data->vecs[1].y * sin_a);
	data->vecs[1].y = (data->vecs[1].x * sin_a) + (data->vecs[1].y * cos_a);
	data->vecs[2].x = (data->vecs[2].x * cos_a) - (data->vecs[1].y * sin_a);
	data->vecs[2].y = (data->vecs[2].x * sin_a) + (data->vecs[1].y * cos_a);
	printf("Rotating!\n");
}

void	movement(t_cub *data, int dir)
{
	double	vx;
	double	vy;
	t_vec2	p;

	p = (t_vec2){data->vecs[0].x, data->vecs[0].y};
	vx = data->vecs[1].x * MV;
	vy = data->vecs[1].y * MV;
	if (dir == 1 && data->map[(int)(p.y + vy)][(int)(p.x + vx)] != '1')
		data->vecs[0] = (t_vec2){p.x + vx, p.y + vy};
	else if (dir == 2 && data->map[(int)(p.y - vy)][(int)(p.x - vx)] != '1')
		data->vecs[0] = (t_vec2){p.x - vx, p.y - vy};
	else if (dir == 3 && data->map[(int)(p.y - vx)][(int)(p.x + vy)] != '1')
		data->vecs[0] = (t_vec2){p.x + vy, p.y - vx};
	else if (dir == 4 && data->map[(int)(p.y + vx)][(int)(p.x - vy)] != '1')
		data->vecs[0] = (t_vec2){p.x - vy, p.y + vx};
	printf("moving!\n");
}

void	paint(t_cub *data)
{
	unsigned int	x;
	unsigned int	y;
	int32_t			f;
	int32_t			c;

	f = col(data->cols[0].x, data->cols[0].y, data->cols[0].z);
	c = col(data->cols[1].x, data->cols[1].y, data->cols[1].z);
	x = -1;
	while (++x < data->img->width)
	{
		y = 0;
		while (y < data->img->height / 2)
			mlx_put_pixel(data->img, x, y++, c);
		while (y < data->img->height)
			mlx_put_pixel(data->img, x, y++, f);
	}
}

void	get_info(t_cub *data, t_ray *ray, short x, t_vec2 *dist)
{
	double	cam_x;

	cam_x = (2 * x / (double)data->img->width - 1);
	ray->dir = (t_vec2) {data->vecs[1].x + (data->vecs[2].x * cam_x),
			data->vecs[1].y + (data->vecs[2].y * cam_x)};
	if (ray->dir.x)
			dist->x = fabs(1 / ray->dir.x);
	else
		dist->x = INFINITY;
	if (ray->dir.y)
		dist->y = fabs(1 / ray->dir.y);
	else
		dist->y = INFINITY;
	ray->pos = (t_vec2){data->vecs[0].x, data->vecs[0].y};

}

void	fix_ray(t_cub *data, t_ray *ray, t_vec2 (*vecs)[3], t_vec2 *dist)
{
	if (ray->dir.y < 0)
	{
		vecs[0][0].y = -1;
		vecs[0][1].y = (data->vecs[0].y - ray->pos.y) * dist->y;
		vecs[0][2].y = 0;
	}
	else
	{
		vecs[0][0].y = 1;
		vecs[0][1].y = (ray->pos.y + 1.0 - data->vecs[0].y) * dist->y;
		vecs[0][2].y = 1;
	}	
	if (ray->dir.x >= 0)
	{
		vecs[0][0].x = 1;
		vecs[0][1].x = (ray->pos.x + 1.0 - data->vecs[0].x) * dist->x;
		vecs[0][2].x = 2;
	}
	else
	{
		vecs[0][0].x = -1;
		vecs[0][1].x = (data->vecs[0].x - ray->pos.x) * dist->x;
		vecs[0][2].x = 3;
	}
}

void	launch_ray(t_cub *data, t_ray *ray, t_vec2 *dist, t_vec2 (*vecs)[3])
{
	while (1)
	{
		if (vecs[0][1].x < vecs[0][1].y)
		{
			vecs[0][1].x += dist->x;
			ray->pos.x += vecs[0][0].x;
			ray->axis = 'X';
		}
		else
		{
			vecs[0][1].y += dist->y;
			ray->pos.y += vecs[0][0].y;
			ray->axis = 'Y';
		}
		if (data->map[(int)ray->pos.y][(int)ray->pos.x] == '1')
			break ;
	}
}

static void	set_struct(t_texture *t, t_ray *r, t_cub *g)
{
	t->line_height = (g->img->height) / r->distance;
	t->start = (g->img->height / 2) - (t->line_height / 2);
	t->end = (g->img->height / 2) + (t->line_height / 2);
	if (t->start < 0)
		t->start = 0;
	if (t->end >= (int)(g->img->height))
		t->end = g->img->height - 1;
	if (r->axis == 'X')
		t->wall_x = g->vecs[0].y + (r->distance * r->dir.y);
	else
		t->wall_x = g->vecs[0].x + (r->distance * r->dir.x);
	t->wall_x -= floor(t->wall_x);
	t->pxl[0] = (int)(t->wall_x * (double)g->tex[r->hit]->width);
	if ((r->axis == 'X' && r->dir.x > 0) \
	|| (r->axis == 'Y' && r->dir.y < 0))
		t->pxl[0] = g->tex[r->hit]->width - t->pxl[0] - 1;
	t->step = (double)(g->tex[r->hit]->height) / t->line_height;
	t->pos = (t->start - (g->img->height / 2) + (t->line_height / 2)) * t->step;
}

void	render_walls(t_ray *r, short x, t_cub *g)
{
	t_texture		t;
	int32_t			pxl;
	mlx_texture_t	*wall;

	wall = g->tex[r->hit];
	set_struct(&t, r, g);
	while (t.start < t.end)
	{
		t.pxl[1] = t.pos;
		pxl = (t.pxl[1] * wall->width + t.pxl[0]) * 4;
		mlx_put_pixel(g->img, x, t.start, col(wall->pixels[pxl + 0], \
		wall->pixels[pxl + 1], wall->pixels[pxl + 2]));
		t.pos += t.step;
		t.start++;
	}
}

void	raycast(t_cub *data, t_ray *ray)
{
	short		x;
	t_vec2	dist;
	t_vec2	vecs[3]; // step == 0, surf_d == 1, side == 2

	x = -1;
	while (++x < data->img->width)
	{
		get_info(data, ray, x, &dist);		
		fix_ray(data, ray, &vecs, &dist);
		launch_ray(data, ray, &dist, &vecs);
		if (ray->axis == 'X')
		{
			ray->distance = vecs[1].x - dist.x;
			ray->hit = vecs[2].x;
		}
		else
		{
			ray->distance = vecs[1].y - dist.y;
			ray->hit = vecs[2].y;
		}
		render_walls(ray, x, data);
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

void	set_vec(char c, t_cub *data)
{
	if (c == 'N')
	{
		data->vecs[1] = (t_vec2){0, -1};
		data->vecs[2] = (t_vec2){FOV, 0};
	}
	else if (c == 'S')
	{
		data->vecs[1] = (t_vec2){0, 1};
		data->vecs[2] = (t_vec2){FOV * -1, 0};
	}
	else if (c == 'E')
	{
		data->vecs[1] = (t_vec2){-1, 0};
		data->vecs[2] = (t_vec2){0, FOV * -1};
	}
	else if (c == 'W')
	{
		data->vecs[1] = (t_vec2){1, 0};
		data->vecs[2] = (t_vec2){0, FOV};
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

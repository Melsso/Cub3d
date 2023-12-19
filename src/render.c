/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:53:55 by smallem           #+#    #+#             */
/*   Updated: 2023/12/19 19:46:42 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_camera(t_cub *data, int dir)
{
	if (dir == 1)
	{
		data->p.pa += 5;
		data->p.pa = fixAng(data->p.pa);
		data->p.dx = cos(degToRad(data->p.pa));
		data->p.dy = -sin(degToRad(data->p.pa));
	}
	if (dir == 2)
	{
		data->p.pa -= 5;
		data->p.pa = fixAng(data->p.pa);
		data->p.dx = cos(degToRad(data->p.pa));
		data->p.dy = -sin(degToRad(data->p.pa));
	}
	draw_rays(data);
}

void	movement(t_cub *data, int dir)
{
	if (dir == 1 && data->no->instances[0].y - 32 >= 0)
		data->no->instances[0].y -= 32;
	else if (dir == 2 && data->no->instances[0].y + 32 <= 512 - 64)
		data->no->instances[0].y += 32;
	else if (dir == 3 && data->no->instances[0].x - 32 >= 0)
		data->no->instances[0].x -= 32;
	else if (dir == 4 && data->no->instances[0].x + 32 <= 1024 - 64)
		data->no->instances[0].x += 32;
}

void	events(struct mlx_key_data key, void *param)
{
	t_cub	*data;

	data = param;
	// paint the floor and ceiling here paint()
	// ray cast here raycast()
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		ft_error(NULL, data, NULL, 1);
	if ((key.key == MLX_KEY_W) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 1);
	else if ((key.key == MLX_KEY_S) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 2);
	else if ((key.key == MLX_KEY_A) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 3);
	else if ((key.key == MLX_KEY_D) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 4);
	else if ((key.key == MLX_KEY_RIGHT) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_camera(data, 1);
	else if ((key.key == MLX_KEY_LEFT) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_camera(data, 2);
}

static void	set_vec(char c, t_cub *data)
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

static void	get_data(t_cub *data)
{
	int	i;
	int	j;

	i = -1;
	data->width = 0;
	while (data->map[++i])
	{
		if (ft_strlen(data->map[i]) > data->width)
			data->width = ft_strlen(data->map[i]);
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
	data->height = i;
}

void	init(t_cub *data)
{
	int	i;

	get_data(data);
	data->text[0] = mlx_load_png(data->nop);
	data->text[1] = mlx_load_png(data->sop);
	data->text[2] = mlx_load_png(data->eap);
	data->text[3] = mlx_load_png(data->wep);
	i = -1;
	while (++i < 4)
	{
		if (!data->text[i])
			ft_error("Error\nCould not load textures!", data, NULL, 1);
	}
	data->win = mlx_init(1920, 1080, "Cub3d", false);
	if (!data->win)
		ft_error("Error\nCould not init mlx!", data, NULL, 1);
	data->img = mlx_new_image(data->win, 1920, 1080);
	if (!data->img)
		ft_error("Error\nCould not create image!", data, NULL, 1);
	if (mlx_image_to_window(data->win, data->img, 0, 0) == -1)
		ft_error("Error\nImg2Win mlx failure!", data, NULL, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:48:49 by smallem           #+#    #+#             */
/*   Updated: 2023/12/26 15:14:25 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1
# define FOV 0.66
# define ROT 0.02
# define MV 0.04

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

typedef struct s_vec3
{
	unsigned short	x;
	unsigned short	y;
	unsigned short	z;
}	t_vec3;

typedef struct s_vec2
{
	double	x;
	double	y;
	int		xi;
	int		yi;
}	t_vec2;

typedef struct s_ray
{
	double	distance;
	int		hit;
	char	axis;
	t_vec2	dir;
	t_vec2	pos;
}	t_ray;

typedef struct s_cub
{
	t_vec3			cols[2];
	t_vec2			vecs[3];
	int				h;
	int				w;
	char			**map;
	mlx_t			*win;
	mlx_texture_t	*tex[4];
	mlx_image_t		*img;
}	t_cub;

void	free_split(char **mat);
void	ft_error(char *msg, t_cub *data, char **mat, int flag);
void	call_err(char *msg, t_cub *data, char **mat, char **m);

char	*ft_get_buffer(char *str);
char	*free_all(char *str, char *buffer);
char	*ft_read(char *str, int fd, ssize_t bytes_read);
char	*get_next_line(int fd);

void	read_content(t_cub *data, char **argv);
char	*read_stuff(t_cub *data, int fd);
void	check_contents(char *line, t_cub *data);
void	get_paths(t_cub *data);
void	clean_map(t_cub *data);
void	copy_map(t_cub *data, char **map);
void	check_valid_map(t_cub *data);

void	get_data(t_cub *data);
void	set_vec(char c, t_cub *data);
void	init(t_cub *data);
void	paint(t_cub *data);

void	raycast(t_cub *data, t_ray *ray);
void	get_info(t_cub *data, t_ray *ray, short x, t_vec2 *dist);
void	fix_ray(t_cub *data, t_ray *ray, t_vec2 (*vecs)[3], t_vec2 *dist);
void	launch_ray(t_cub *data, t_ray *ray, t_vec2 *dist, t_vec2 (*vecs)[3]);

void	get_tex_info(t_vec2 (*v)[3], t_ray *ray, t_cub *data);
void	render_walls(t_ray *ray, short x, t_cub *data);

void	events(void *param);
void	movement(t_cub *var, int dir);
void	rotate_camera(t_cub *data, int dir);

//////utils/////

int		is_pos(char c);
int32_t	col(int32_t r, int32_t g, int32_t b);

#endif
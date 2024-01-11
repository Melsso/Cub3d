/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:48:49 by smallem           #+#    #+#             */
/*   Updated: 2024/01/11 13:24:54 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define BUFFER_SIZE 1
# define FOV 0.66
# define ROT 0.02
# define MV 0.02
# define WIDTH 1200
# define HEIGHT 1200

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
}	t_vec2;

typedef struct s_vec
{
	int	x;
	int	y;
}	t_vec;

typedef struct s_ray
{
	double	distance;
	int		hit;
	char	axis;
	t_vec2	dir;
	t_vec	pos;
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
char	**copy_map(t_cub *data, int size);
void	check_valid_map(t_cub *data);
int		rec_valid(char **map, t_cub *data, t_vec v, int flag);

void	get_data(t_cub *data);
void	set_vec(char c, t_cub *data);
void	init(t_cub *data);
void	paint(mlx_image_t *img, t_vec3 *cols);

int32_t	col(int32_t r, int32_t g, int32_t b);
void	raycast(t_cub *data, t_ray *ray);
void	get_info(t_cub *data, t_ray *ray, short x, t_vec2 *dist);
void	fix_ray(t_vec2 *v, t_ray *ray, t_vec2 *vecs, t_vec *vec);
void	launch_ray(char **map, t_ray *ray, t_vec2 *vecs, t_vec *vec);

// void	get_tex_info(t_vec2 (*v)[3], t_ray *ray, t_cub *data);
// void	get_tex_info(t_vec2 *v, t_vec (*ve)[2],t_ray *ray, t_cub *data);

void	render_walls(t_ray *ray, short x, t_cub *data);

void	events(void *param);
int		movement(t_vec2 *vecs, char **map, int dir);
int		rotate_camera(t_vec2 *vecs, short dir);

//////utils/////

int		is_pos(char c);
char	**cp_map(t_cub *data);

#endif
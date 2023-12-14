/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:48:49 by smallem           #+#    #+#             */
/*   Updated: 2023/12/14 19:43:53 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

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

typedef struct s_vec3 t_vec3;
typedef struct s_vec3
{
	int	x;
	int	y;
	int	z;
} t_vec3;

typedef struct	s_pl t_pl;
typedef struct	s_pl
{
	int	x;
	int	y;
	float	dx;
	float	dy;
	float	pa;
} t_pl;

typedef struct s_cub	t_cub;
typedef struct s_cub
{
	char		**map;
	char		*nop;
	char		*sop;
	char		*eap;
	char		*wep;
	mlx_t		*win;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*ea;
	mlx_image_t	*we;
	mlx_image_t	*c;
	mlx_image_t	*f;
	t_vec3		f_col;
	t_vec3		c_col;
	t_pl		p;
	int			cam_dir;
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
void	trim_input(t_cub *data);
void	get_paths(t_cub *data);
void	clean_map(t_cub *data);
void	copy_map(t_cub *data, char **map);
void	check_valid_map(t_cub *data);

void	init(t_cub *data);
void	load_images(t_cub *data);
void	events(struct mlx_key_data key, void *param);
void	movement(t_cub *var, int dir);
void	rotate_camera(t_cub *data, int dir);

//////utils/////
float	degToRad(int a);
int 	fixAng(int a);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:48:49 by smallem           #+#    #+#             */
/*   Updated: 2023/12/11 17:33:52 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
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

typedef struct s_cub	t_cub;
typedef struct s_cub
{
	char		**map;
	char		*nop;
	char		*sop;
	char		*eap;
	char		*wep;
	mlx_image_t	*no;
	mlx_image_t	*so;
	mlx_image_t	*ea;
	mlx_image_t	*we;
	t_vec3		f_col;
	t_vec3		c_col;
}	t_cub;

void	ft_error(char *msg, t_cub *data, char **mat, int flag);
void	read_content(t_cub *data, char **argv);
void	check_contents(char *line, t_cub *data);
void	fill_info(t_cub *data);
void	fill_path(t_cub *data, int i, int flag);

#endif
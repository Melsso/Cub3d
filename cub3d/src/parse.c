/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:00:26 by smallem           #+#    #+#             */
/*   Updated: 2023/12/11 17:33:51 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_path(t_cub *data, int i, int flag)
{
	char	**mat;
	char	*path;

	mat = ft_split(data->map[i], ' ');
	if (!mat)
		ft_error("Error\nMalloc error!", data, NULL, 1);
	if (mat[1] && !mat[2])
	{
		path = ft_strdup(mat[1]);
		if (!path)
			ft_error("Error\nMalloc error", data, mat, 1);
		if (flag == 1)
			data->nop = path;
		if (flag == 2)
			data->sop = path;
		if (flag == 3)
			data->eap = path;
		if (flag == 4)
			data->wep = path;
		free_split(mat);
	}
	else
		ft_error("Error\nInvalid path!", data, mat, 1);
}

t_vec3	fill_vec(char **c, t_cub *data, char **mat)
{
	int		i;
	int		j;
	int		arr[3];
	t_vec3	vec;

	i = 0;
	while (c[i])
		i++;
	if (i != 3)
	{
		free_split(c);
		ft_error("Error\nInvalid color format!", data, mat, 1);
	}
	i = -1;
	while (c[++i])
	{
		j = -1;
		while (c[i][++j])
		{
			if (c[i][j] < '0' || c[i][j] > '9')
			{
				free_split(c);
				ft_error("Error\nInvalid color format!", data, mat, 1);
			}
		}
		arr[i] = ft_atoi(c[i]);
	}
	vec.x = arr[0];
	vec.y = arr[1];
	vec.z = arr[2];
	free_split(c);
	return (vec);
}

void	fill_color(t_cub *data, int i, int flag)
{
	char	**mat;
	char	**c;
	int		i;

	mat = ft_split(data->map[i], ' ');
	if (!mat)
		ft_error("Error\nMalloc error!", data, NULL, 1);
	if (mat[1] && !mat[2])
	{
		c = ft_split(mat[1], ',');
		if (!c)
			ft_error("Error\nMalloc error!", data, mat, 1);
		if (flag == 1)
			data->f_col = fill_vec(c, data, mat);
		if (flag == 2)
			data->c_col = fill_vec(c, data, mat);
		free_split(mat);
	}
	else
		ft_error("Error\nInvalid color format!", data, mat, 1);
}

void	fill_info(t_cub *data)
{
	int	i;

	i = -1;
	while (data->map[++i])
	{
		if (!ft_strncmp(data->map[i], "NO", 2))
			fill_path(data, i, 1);
		else if (!ft_strncmp(data->map[i], "SO", 2))
			fill_path(data, i, 2);
		else if (!ft_strncmp(data->map[i], "EA", 2))
			fill_path(data, i, 3);
		else if (!ft_strncmp(data->map[i], "WE", 2))
			fill_path(data, i, 4);
		else if (!ft_strncmp(data->map[i], "F", 1))
			fill_color(data, i, 1);
		else if (!ft_strncmp(data->map[i], "C", 1))
			fill_color(data, i, 2);
	}
}

void	check_map(t_cub *data)
{
	
}

void	check_contents(char *line, t_cub *data)
{
	int	i;
	int	count;

	data->map = ft_split(line, '\n');
	free(line);
	if (!data->map)
		ft_error("Error\nMalloc error!", NULL, NULL, 0);
	i = -1;
	count = 0;
	while (data->map[++i])
	{
		if (!ft_strncmp(data->map[i], "NO", 2)
			|| !ft_strncmp(data->map[i], "SO", 2)
			|| !ft_strncmp(data->map[i], "WE", 2)
			|| !ft_strncmp(data->map[i], "EA", 2)
			|| !ft_strncmp(data->map[i], "F", 1)
			|| !ft_strncmp(data->map[i], "C", 1))
			count++;
	}
	if (count != 6)
		ft_error("Error\nIncomplete map", data, NULL, 1);
	fill_info(data);
	check_map(data);
}

void	read_content(t_cub *data, char **argv)
{
	int		fd;
	int		i;
	char	*line;
	char	*tmp;
	char	*t;

	i = ft_strlen(argv[1]);
	if (i < 4)
		ft_error("Error\nBad file name", NULL, NULL, 0);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4))
		ft_error("Error\nBad file format", NULL, NULL, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCould not open file!", NULL, NULL, 0);
	line = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		t = line;
		line = ft_strjoin(t, tmp);
		free(tmp);
		free(t);
	}
	check_contents(line, data);
}

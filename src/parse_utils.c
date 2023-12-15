/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:54:23 by smallem           #+#    #+#             */
/*   Updated: 2023/12/15 18:56:43 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_line(t_cub *data, char **mat, char *str)
{
	char	*path;

	if (mat[0] && !ft_strncmp(mat[0], str, ft_strlen(mat[0])) && mat[1]
		&& !mat[2])
	{
		path = ft_strdup(mat[1]);
		if (!path)
			ft_error("Error\nMalloc error!", data, mat, 1);
		if (!ft_strncmp(str, "NO", 2))
			data->nop = path;
		if (!ft_strncmp(str, "SO", 2))
			data->sop = path;
		if (!ft_strncmp(str, "EA", 2))
			data->eap = path;
		if (!ft_strncmp(str, "WE", 2))
			data->wep = path;
		free_split(mat);
		free(str);
	}
	else
	{
		free(str);
		ft_error("Error\nBad texture path!", data, mat, 1);
	}
}

static int	check_colors(t_cub *data, char **mat, char **m)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (m[++i])
	{
		tmp = m[i];
		m[i] = ft_strtrim(tmp, " \t");
		free(tmp);
		if (!m[i])
			call_err("Error\nMalloc error!", data, mat, m);
		j = -1;
		while (m[i][++j])
		{
			if (m[i][j] < '0' || m[i][j] > '9')
				call_err("Error\nBad color format", data, mat, m);
		}
	}
	if (i != 3)
		call_err("Error\nBad color format", data, mat, m);
	return (1);
}

static void	get_colors(t_cub *data, char **mat, int ind)
{
	char	**m;
	t_vec3	vec;

	if (!mat)
		ft_error("Error\nMalloc error!", data, NULL, 1);
	if (mat[0] && (!ft_strncmp(mat[0], "C", ft_strlen(mat[0]))
			|| !ft_strncmp(mat[0], "F", ft_strlen(mat[0]))) && mat[1]
		&& !mat[2])
	{
		m = ft_split(mat[1], ',');
		if (!m)
			ft_error("Error\nMalloc error!", data, mat, 1);
		if (check_colors(data, mat, m))
		{
			vec = (t_vec3){ft_atoi(m[0]), ft_atoi(m[1]), ft_atoi(m[2])};
			if (data->map[ind][0] == 'F')
				data->f_col = vec;
			else
				data->c_col = vec;
		}
		free_split(mat);
		free_split(m);
	}
	else
		ft_error("Error\nBad color format!", data, mat, 1);
}

void	get_paths(t_cub *data)
{
	int		i;
	char	**mat;
	char	*str;

	i = -1;
	while (data->map[++i])
	{
		if (!ft_strncmp(data->map[i], "NO", 2) || !ft_strncmp(data->map[i],
				"SO", 2) || !ft_strncmp(data->map[i], "EA", 2)
			|| !ft_strncmp(data->map[i], "WE", 2))
		{
			mat = ft_split(data->map[i], ' ');
			if (!mat)
				ft_error("Error\n", data, NULL, 1);
			str = ft_substr(data->map[i], 0, 2);
			if (!str)
				ft_error("Error\nMalloc error!", data, mat, 1);
			check_line(data, mat, str);
		}
		else if (data->map[i][0] == 'F' || data->map[i][0] == 'C')
		{
			mat = ft_split(data->map[i], ' ');
			get_colors(data, mat, i);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:03:34 by smallem           #+#    #+#             */
/*   Updated: 2024/01/16 11:48:08 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_map(t_cub *data)
{
	int		i;
	int		j;
	char	**map;

	i = -1;
	j = 0;
	while (data->map[++i])
	{
		if (!ft_strncmp(data->map[i], "NO", 2) || !ft_strncmp(data->map[i],
				"SO", 2) || !ft_strncmp(data->map[i], "WE", 2)
			|| !ft_strncmp(data->map[i], "EA", 2) || !ft_strncmp(data->map[i],
				"F", 1) || !ft_strncmp(data->map[i], "C", 1))
			j++;
		if (i == 5 && j != 6)
			ft_error("Error\nInput data format not respected!", data, NULL, 1);
	}
	map = copy_map(data, i - 6 + 1);
	free_split(data->map);
	data->map = map;
}

static int	is_inset(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S'
		|| c == 'W' || c == ' ')
		return (1);
	return (0);
}

void	check_valid_map(t_cub *data)
{
	int		arr[3];
	t_vec3	vec;
	char	**m;

	arr[0] = 1;
	arr[2] = 0;
	while (data->map[++arr[0]])
	{
		arr[1] = -1;
		while (data->map[arr[0]][++arr[1]])
		{
			if (!is_inset(data->map[arr[0]][arr[1]]))
				ft_error("Error\nInvalid characters in map!", data, NULL, 1);
			if (is_pos(data->map[arr[0]][arr[1]]))
				vec = (t_vec3){arr[0], arr[1], arr[2]++};
		}
	}
	m = cp_map(data);
	if (arr[2] != 1)
		ft_error("Error\nMultiple/No initial direction!", data, m, 1);
	else
		rec_valid(m, data, (t_vec){vec.x, vec.y}, 0);
	free_split(m);
}

int	rec_valid(char **map, t_cub *data, t_vec v, int flag)
{
	if ((v.x < 0 || v.y < 0 || !map[v.x] || v.y >= (int)ft_strlen(map[v.x])
			|| !map[v.x][v.y]) && flag)
		ft_error("Error\nMap not closed properly", data, map, 0);
	if (v.x < 0 || v.y < 0 || !map[v.x] || v.y >= (int)ft_strlen(map[v.x])
		|| !map[v.x][v.y])
		return (0);
	if (map[v.x][v.y] == '1' || map[v.x][v.y] == 'V')
		return (0);
	if (map[v.x][v.y] == ' ')
		ft_error("Error\nMap not closed properly", data, map, 0);
	if (map[v.x][v.y] == '0' || is_pos(map[v.x][v.y]))
	{
		map[v.x][v.y] = 'V';
		rec_valid(map, data, (t_vec){v.x + 1, v.y}, 1);
		rec_valid(map, data, (t_vec){v.x, v.y + 1}, 1);
		rec_valid(map, data, (t_vec){v.x - 1, v.y}, 1);
		rec_valid(map, data, (t_vec){v.x, v.y - 1}, 1);
	}
	return (0);
}

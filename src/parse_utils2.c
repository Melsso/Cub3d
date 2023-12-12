/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:03:34 by smallem           #+#    #+#             */
/*   Updated: 2023/12/12 18:28:36 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_map(t_cub *data)
{
	int		i;
	int		j;
	char	*line;
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
	map = (char **)malloc(sizeof(char *) * (i - 6 + 1));
	if (!map)
		ft_error("Error\nMalloc error!", data, NULL, 1);
	copy_map(data, map);
}

static int	is_inset(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

static int	is_pos(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	check_valid_map(t_cub *data)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if ((i == 0 || !data->map[i + 1] || j == 0 || j
					== ft_strlen(data->map[i]) - 1) && data->map[i][j] != '1')
				ft_error("Error\nMap is not closed!", data, NULL, 1);
			if (!is_inset(data->map[i][j]))
				ft_error("Error\nInvalid characters in map!", data, NULL, 1);
			if (is_pos(data->map[i][j]))
				count++;
		}
	}
	if (count != 1)
		ft_error("Error\nMultiple Initial positions!", data, NULL, 1);
}

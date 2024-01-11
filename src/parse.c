/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:00:26 by smallem           #+#    #+#             */
/*   Updated: 2024/01/11 12:54:47 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	get_paths(data);
}

char	*read_stuff(t_cub *data, int fd)
{
	char	*line;
	char	*tmp;
	char	*t;

	line = ft_strdup("");
	if (!line)
	{
		close(fd);
		ft_error("Error\nMalloc error!", NULL, NULL, 0);
	}
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
	close(fd);
	return (line);
}

char	**copy_map(t_cub *data, int size)
{
	int		i;
	int		j;
	char	*line;
	char	**map;

	map = (char **)malloc(sizeof(char *) * size);
	if (!map)
		ft_error("Error\nMalloc error!", data, NULL, 0);
	i = 5;
	j = 0;
	while (data->map[++i])
	{
		map[j] = ft_strdup(data->map[i]);
		if (!map[j++])
			ft_error("Error\nMalloc error!", data, map, 1);
	}
	map[j] = NULL;
	return (map);
}

void	read_content(t_cub *data, char **argv)
{
	int		fd;
	int		i;
	char	*line;

	i = ft_strlen(argv[1]);
	if (i < 4)
		ft_error("Error\nBad file name", NULL, NULL, 0);
	if (ft_strncmp(&argv[1][i - 4], ".cub", 4))
		ft_error("Error\nBad file format", NULL, NULL, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error("Error\nCould not open file!", NULL, NULL, 0);
	line = read_stuff(data, fd);
	check_contents(line, data);
	clean_map(data);
	check_valid_map(data);
}

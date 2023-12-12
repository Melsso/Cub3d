/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:09:17 by smallem           #+#    #+#             */
/*   Updated: 2023/12/12 17:24:33 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split(char **mat)
{
	int	i;

	if (!mat)
		return ;
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		mat[i++] = NULL;
	}
	mat = NULL;
}

void	call_err(char *msg, t_cub *data, char **mat, char **m)
{
	free_split(m);
	ft_error(msg, data, mat, 1);
}

void	ft_error(char *msg, t_cub *data, char **mat, int flag)
{
	if (flag)
	{
		if (data->nop)
			free(data->nop);
		if (data->sop)
			free(data->sop);
		if (data->wep)
			free(data->wep);
		if (data->eap)
			free(data->eap);
	}
	if (msg)
		printf("%s\n", msg);
	if (mat)
		free_split(mat);
	exit(1);
}

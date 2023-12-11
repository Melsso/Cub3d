/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:09:17 by smallem           #+#    #+#             */
/*   Updated: 2023/12/11 16:57:58 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *msg, t_cub *data, char **mat, int flag)
{
	if (flag)
		// free struct
	if (msg)
		printf("%s\n", msg);
	if (mat)
		free_split(mat);
	exit(1);
}

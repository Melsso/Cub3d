/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smallem <smallem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:53:55 by smallem           #+#    #+#             */
/*   Updated: 2023/12/15 19:22:06 by smallem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	print_r(t_cub *data, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    while (1)
    {
		mlx_put_pixel(data->f, x0, y0, 0xFF0000FF);
		
        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
	mlx_image_to_window(data->win, data->f, 0, 0);
}

static void	draw_rays(t_cub *data)
{
	int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
 
	ra=fixAng(data->p.pa+30);                                                              //ray set back 30 degrees
	int map[]=
	{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,
	1,0,1,1,0,0,0,0,0,1,1,1,0,0,0,1,
	1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	};

	for(r=0;r<60;r++)
	{
  //---Vertical--- 
		dof=0; side=0; disV=100000;
		float Tan=tan(degToRad(ra));
		if(cos(degToRad(ra))> 0.001){ rx=(((int)data->p.x>>6)<<6)+64;      ry=(data->p.x-rx)*Tan+data->p.y; xo= 64; yo=-xo*Tan;}//looking left
		else if(cos(degToRad(ra))<-0.001){ rx=(((int)data->p.x>>6)<<6) -0.0001; ry=(data->p.x-rx)*Tan+data->p.y; xo=-64; yo=-xo*Tan;}//looking right
		else { rx=data->p.x; ry=data->p.y; dof=8;}                                                  //looking up or down. no hit  

		while(dof<8) 
		{ 
			mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*16+mx;                     
			if(mp>0 && mp<16*8 && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-data->p.x)-sin(degToRad(ra))*(ry-data->p.y);}//hit         
			else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
  		} 
		vx=rx; vy=ry;

  //---Horizontal---
		dof=0; disH=100000;
		Tan=1.0/Tan; 
		if(sin(degToRad(ra))> 0.001){ ry=(((int)data->p.y>>6)<<6) -0.0001; rx=(data->p.y-ry)*Tan+data->p.x; yo=-64; xo=-yo*Tan;}//looking up 
		else if(sin(degToRad(ra))<-0.001){ ry=(((int)data->p.y>>6)<<6)+64;      rx=(data->p.y-ry)*Tan+data->p.x; yo= 64; xo=-yo*Tan;}//looking down
		else{ rx=data->p.x; ry=data->p.y; dof=8;}                                                   //looking straight left or right
 
		while(dof<8) 
		{ 
		mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*16+mx;                          
		if(mp>0 && mp<16*8 && map[mp] == 1){ dof=8; disH=cos(degToRad(ra))*(rx-data->p.x)-sin(degToRad(ra))*(ry-data->p.y);}//hit         
		else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
		} 
  
		if(disV<disH){ rx=vx; ry=vy; disH=disV;}    
		print_r(data, data->p.x, data->p.y, rx, ry);              //horizontal hit first
    
		int ca=fixAng(data->p.pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
		int lineH = (64*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
		int lineOff = 160 - (lineH>>1);                                               //line offset
  
		ra=fixAng(ra-1);                                                              //go to next ray
	}

}

void	rotate_camera(t_cub *data, int dir)
{
	if (dir == 1)
	{
		data->p.pa += 5;
		data->p.pa = fixAng(data->p.pa);
		data->p.dx = cos(degToRad(data->p.pa));
		data->p.dy = -sin(degToRad(data->p.pa));
	}
	if (dir == 2)
	{
		data->p.pa -= 5;
		data->p.pa = fixAng(data->p.pa);
		data->p.dx = cos(degToRad(data->p.pa));
		data->p.dy = -sin(degToRad(data->p.pa));
	}
	draw_rays(data);
}

void	movement(t_cub *data, int dir)
{
	if (dir == 1 && data->no->instances[0].y - 32 >= 0)
		data->no->instances[0].y -= 32;
	else if (dir == 2 && data->no->instances[0].y + 32 <= 512 - 64)
		data->no->instances[0].y += 32;
	else if (dir == 3 && data->no->instances[0].x - 32 >= 0)
		data->no->instances[0].x -= 32;
	else if (dir == 4 && data->no->instances[0].x + 32 <= 1024 - 64)
		data->no->instances[0].x += 32;
}

void	events(struct mlx_key_data key, void *param)
{
	t_cub	*data;

	data = param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		ft_error(NULL, data, NULL, 1);
	if ((key.key == MLX_KEY_W) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 1);
	else if ((key.key == MLX_KEY_S) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 2);
	else if ((key.key == MLX_KEY_A) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 3);
	else if ((key.key == MLX_KEY_D) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		movement(data, 4);
	else if ((key.key == MLX_KEY_RIGHT) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_camera(data, 1);
	else if ((key.key == MLX_KEY_LEFT) && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
		rotate_camera(data, 2);
}

void	init(t_cub *data)
{
	xpm_t	*xpm;

	data->win = mlx_init(1024, 512, "Cub3d", 0);
	data->no = mlx_new_image(data->win, 32, 32);
	ft_memset(data->no->pixels, 255, data->no->width * data->no->height * sizeof(int32_t));
	data->f = mlx_new_image(data->win, 1024, 512);
	data->p.x = 512;
	data->p.y = 256 - 16;
	data->p.pa = 180;
	data->p.dx = cos(degToRad(data->p.pa));
	data->p.dy = -sin(degToRad(data->p.pa));
	xpm = mlx_load_xpm42("./textures/wall.xpm42");
	if (!xpm)
		ft_error("Error\nCould not load xpm file!", data, NULL, 1);
	data->so = mlx_texture_to_image(data->win, &xpm->texture);
	if (!data->so)
		ft_error("Error\nCould not load image!", data, NULL, 1);
	
	mlx_image_to_window(data->win, data->no, 512 - 16, 256 - 16);

	mlx_key_hook(data->win, events, data);
	mlx_loop(data->win);
	mlx_terminate(data->win);
}

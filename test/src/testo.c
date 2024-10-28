/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:17:34 by lrichaud          #+#    #+#             */
/*   Updated: 2024/09/28 15:30:04 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "../minilibx-linux/mlx.h"
#include "../../headers/cube3d.h"
// #include "../libft/libft.h"


#define WIDTH 1920
#define HEIGHT 1080

double	delta_dir(double ray_dir);
int		mlx(void);

t_data	new_img(t_mlx *vars, int width, int height)
{
	t_data	frame;

	frame.img = mlx_new_image(vars->mlx, width, height);
	if (!frame.img)
	{
		frame.addr = NULL;
		return (frame);
	}
	frame.addr = mlx_get_data_addr(frame.img, &frame.bits_per_pixel, \
		&frame.line_length, &frame.endian);
	return (frame);
}

int	ray_dist(void)
{
	int	worldMap[24][24]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	double	rayDirX;
	double	deltaDistX;
	double	rayDirY;
	double	deltaDistY;
	double	cameraX;
	double	posX = 22, posY = 12;
	double	dirX = -1, dirY = 0.5;
	double	planeX = 0, planeY = 0.66;
	int		x;
	int		w;
	int		stepX;
	int		stepY;
	int		mapX = (int)posX;
	int		mapY = (int)posY;
	double	sideDistX;
	double	sideDistY;
	int	hit;
	// int	side;

	hit = 0;
	w = 1000;
	x = 0;
	while (x < w)
	{
		cameraX = 2 * x / (double) w - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		deltaDistX = delta_dir(rayDirX);
		deltaDistY = delta_dir(rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		x++;
	}
	mlx();

	return (0);
}

double	delta_dir(double ray_dir)
{
	if (ray_dir == 0)
		return (1e30);
	else
		return (fabs(1 / ray_dir));
}

int	mlx(void)
{
	t_mlx	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Cube3D");
	vars.img = new_img(&vars, WIDTH, HEIGHT);
	vars.distance = 300;
	mlx_loop(vars.mlx);
	return (1);
}

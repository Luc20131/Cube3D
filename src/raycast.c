/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:56:26 by lrichaud          #+#    #+#             */
/*   Updated: 2024/11/01 12:27:38 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cube3d.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int	raycast(t_mlx *vars)
{
	t_data img;

	img = vars->img;
	t_pos	origin;
	origin = get_carac_pos(vars->map, &vars->offset);
	printf("x : %d y :%d\n",origin.x, origin.y);
	double posX = origin.x, posY = origin.y;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	double perpWallDist;
	double stepX;
	double stepY;
	origin.x = 0;
	double sideDistX;
	double sideDistY;
	int	side;
	int hit = 0;

	while (origin.x < WIDTH)
	{
		double cameraX = 2 * 5 / (double)WIDTH - 1;
		double rayDirX = dirX + planeX*cameraX;
		double rayDirY = dirY + planeY*cameraX;
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));

		int mapX = 2;
		int mapY = 2 ;
		printf("x : %d y :%d\n",mapX, mapY);

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
			if (vars->map[mapX][mapY] == '1')
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		printf("distance : %lf\n", perpWallDist);
		int lineHeight = (int)(HEIGHT / perpWallDist) * 5;
		t_pos	end;

		origin.y = -lineHeight  + HEIGHT / 2;
		if (origin.y < 0)
			origin.y = 0;
		end = origin;
		end.y = lineHeight  + HEIGHT / 2;
		if(end.y >= HEIGHT)
			end.y = HEIGHT - 1;

		t_pos	current;

		current.x = origin.x;
		current.y = 0;
		while (current.y < origin.y)
		{
			my_mlx_pixel_put(&img, current.x, current.y, 0x00000000);
			current.y++;
		}
		while (current.y < end.y)
		{
			my_mlx_pixel_put(&img, current.x, current.y, create_trgb(255, 255, 255, 255));
			current.y++;
		}
		while (current.y < HEIGHT)
		{
			my_mlx_pixel_put(&img, current.x, current.y, 0x00000000);
			current.y++;
		}
		dirX+= 0.001;
		origin.x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	return (0);
}

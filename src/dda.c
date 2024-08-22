/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:25:08 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/22 16:30:13 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray_dda(t_gamedata *data, float ray_angle)
{
	bool	collision;
	int		side;
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	dx;
	float	dy;
	float	x_dist;
	float	y_dist;
	int		step_x;
	int		step_y;
	float	camera_dist;

	collision = 0;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	map_x = (int)data->playerdata->x_pos;
	map_y = (int)data->playerdata->y_pos;
	dx = fabs(1 / ray_dir_x);
	dy = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		x_dist = (data->playerdata->x_pos - map_x) * dx;
	}
	else
	{
		step_x = 1;
		x_dist = (map_x + 1.0 - data->playerdata->x_pos) * dx;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		y_dist = (data->playerdata->y_pos - map_y) * dy;
	}
	else
	{
		step_y = 1;
		y_dist = (map_y + 1.0 - data->playerdata->y_pos) * dy;
	}

	while (!collision)
	{
		if (x_dist < y_dist)
		{
			x_dist += dx;
			map_x += step_x;
			side = 0; 
		} 
		else
		{
			y_dist += dy;
			map_y += step_y;
			side = 1; 
		}
		if (data->map[map_y][map_x] == '1')
			collision = 1;
	}
	if (!side)
		camera_dist = (map_x - data->playerdata->x_pos + (1 - step_x) / 2) / ray_dir_x;
	else 
		camera_dist = (map_y - data->playerdata->y_pos + (1 - step_y) / 2) / ray_dir_y;

//	data->intersection.distance = data->intersection.distance * cos(data->playerdata->angle - ray_angle);
	data->intersection.distance = camera_dist;
	data->intersection.x = data->playerdata->x_pos + camera_dist * ray_dir_x;
	data->intersection.y = data->playerdata->y_pos + camera_dist * ray_dir_y;
	data->intersection.side = side; 
	if (!side)
	{
		if (ray_dir_x > 0)
			data->intersection.direction = WEST;
		else
			data->intersection.direction = EAST;
	}
	else
	{
		if (ray_dir_y > 0)
			data->intersection.direction = NORTH;
		else
			data->intersection.direction = SOUTH;
	}
}

void	update_intersect(t_gamedata *data, t_raydata *rays)
{

	data->intersection.distance = rays->camera_dist;
	data->intersection.x = data->playerdata->x_pos + rays->camera_dist * rays->ray_dir_x;
	data->intersection.y = data->playerdata->y_pos + rays->camera_dist * rays->ray_dir_y;
	data->intersection.side = rays->side; 
	if (!rays->side)
	{
		if (rays->ray_dir_x > 0)
			data->intersection.direction = WEST;
		else
			data->intersection.direction = EAST;
	}
	else
	{
		if (rays->ray_dir_y > 0)
			data->intersection.direction = NORTH;
		else
			data->intersection.direction = SOUTH;
	}
}

void	check_collisions(t_gamedata *data, t_raydata *rays)
{
	while (!rays->collided)
	{
		if (rays->x_dist < rays->y_dist)
		{
			rays->x_dist += rays->dx;
			rays->map_x += rays->step_x;
			rays->side = 0; 
		} 
		else
		{
			rays->y_dist += rays->dy;
			rays->map_y += rays->step_y;
			rays->side = 1; 
		}
		if (data->map[rays->map_y][rays->map_x] == '1')
			rays->collided = 1;
	}
	if (!rays->side)
		rays->camera_dist = (rays->map_x - data->playerdata->x_pos + (int)(1 - rays->step_x) /2) / rays->ray_dir_x;
	else 
		rays->camera_dist = (rays->map_y - data->playerdata->y_pos + (int)(1 - rays->step_y) / 2) / rays->ray_dir_y;
}


void	calculate_step(t_gamedata *data, t_raydata *rays)
{
	if (rays->ray_dir_x < 0)
	{
		rays->step_x = -1;
		rays->x_dist = (data->playerdata->x_pos - rays->map_x) * rays->dx;
	}
	else
	{
		rays->step_x = 1;
		rays->x_dist = (rays->map_x + 1.0 - data->playerdata->x_pos) * rays->dx;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->step_y = -1;
		rays->y_dist = (data->playerdata->y_pos - rays->map_y) * rays->dy;
	}
	else
	{
		rays->step_y = 1;
		rays->y_dist = (rays->map_y + 1.0 - data->playerdata->y_pos) * rays->dy;
	}
}

void	init_raydata(t_gamedata *data, t_raydata *rays, float ray_angle)
{
	rays->collided = 0;
	rays->ray_dir_x = cos(ray_angle);
	rays->ray_dir_y = sin(ray_angle);
	rays->map_x = (int)data->playerdata->x_pos;
	rays->map_y = (int)data->playerdata->y_pos;
	rays->dx = fabs(1 / rays->ray_dir_x);
	rays->dy = fabs(1 / rays->ray_dir_y);
}


void	print_raydata(t_raydata *rays)
{
	printf("printing raydata contents:\n");
	printf("ray_dir_x:%f\n", rays->ray_dir_x);
	printf("step_x:%d\n", rays->step_x);
	printf("dx:%d\n", rays->dx);
	printf("ray_dir_y:%f\n", rays->ray_dir_y);
	printf("step_y:%d\n", rays->step_y);
	printf("dy:%d\n", rays->dy);
	printf("direction:%d\n", rays->direction);
	printf("side:%d\n", rays->side);
	printf("collision status:%d\n", rays->collided);
	printf("camera distance:%f\n", rays->camera_dist);
	printf("x_distance:%f\n", rays->x_dist);
	printf("y_distance:%f\n", rays->y_dist);
	printf("map x value:%d\n", rays->map_x);
	printf("map y value:%d\n", rays->map_y);
}

void	dda_new(t_gamedata *data, float rayangle)
{
	t_raydata rays;

//	rays = data->rays;
	ft_memset(&rays, 0, sizeof(t_raydata));
	init_raydata(data, &rays, rayangle);
	calculate_step(data, &rays);
	check_collisions(data, &rays);
	update_intersect(data, &rays);
	print_raydata(&rays);
//	printf("value of x intersection:%f\n", data->intersection.x);
//	printf("value of y intersection:%f\n", data->intersection.y);
}

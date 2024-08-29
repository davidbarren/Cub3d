/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:25:08 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 16:14:48 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	update_intersect(t_gamedata *data, t_raydata *rays)
{
	data->intersection.distance = rays->camera_dist;
	data->intersection.x = data->playerdata->x_pos
		+ rays->camera_dist * rays->ray_dir_x;
	data->intersection.y = data->playerdata->y_pos
		+ rays->camera_dist * rays->ray_dir_y;
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
		rays->camera_dist = (rays->map_x - data->playerdata->x_pos
				+ (int)(1 - rays->step_x) / 2) / rays->ray_dir_x;
	else
		rays->camera_dist = (rays->map_y - data->playerdata->y_pos
				+ (int)(1 - rays->step_y) / 2) / rays->ray_dir_y;
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

void	dda_new(t_gamedata *data, float rayangle)
{
	t_raydata	rays;

	ft_memset(&rays, 0, sizeof(t_raydata));
	init_raydata(data, &rays, rayangle);
	calculate_step(data, &rays);
	check_collisions(data, &rays);
	update_intersect(data, &rays);
}

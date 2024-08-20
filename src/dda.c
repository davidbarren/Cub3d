/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:25:08 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/20 16:30:05 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void cast_ray_dda(t_gamedata *data, float ray_angle)
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
	ray_dir_y= sin(ray_angle);
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
/*
 * es para separar dda en 4 o 5 funciones, todavia no funciona
void	init_raydata(t_gamedata *data, t_raydata *rays, float ray_angle)
{
	rays->ray_dir_x = cos(ray_angle);
	rays->ray_dir_y = sin(ray_angle);
	rays->dx = fabs(1 / rays->ray_dir_x);
	rays->dy = fabs(1 / rays->ray_dir_y);
	rays->x_grid = (int) data->playerdata->x_pos;
	rays->y_grid = (int) data->playerdata->y_pos;
	if (rays->ray_dir_x < 0)
	{
		rays->x_step = -1;
		rays->x_wall_dist = (data->playerdata->x_pos - rays->x_grid) * rays->dx;
	}
	else
	{
		rays->x_step = 1;
		rays->x_wall_dist = (rays->x_grid + 1.0f - data->playerdata->x_pos) * rays->dx;
	}
	if (rays->ray_dir_y < 0)
	{
		rays->y_step = -1;
		rays->y_wall_dist = (data->playerdata->y_pos - rays->y_grid) * rays->dy;
	}
	else
	{
		rays->y_step = 1;
		rays->y_wall_dist = (rays->y_grid + 1.0f - data->playerdata->y_pos) * rays->dy;
	}
}
void	check_collisions(t_gamedata *data, t_raydata *rays)
{
	while(!rays->collided)
	{
		if(rays->x_wall_dist < rays->y_wall_dist)
		{
			rays->x_wall_dist += rays->dx;
			rays->x_grid += rays->x_step;
			rays->vertical = 1;
		}
		else
		{
			rays->y_wall_dist += rays->dy;
			rays->y_grid += rays->y_step;
			rays->vertical = 0;
		}
		if (data->map[rays->y_grid][rays->x_grid] == '1')
			rays->collided = 1;
	}
	if (rays->vertical)
		rays->camera_dist = (rays->x_grid - data->playerdata->x_pos + (1 - rays->x_step) / 2) / rays->ray_dir_x;
	else
		rays->camera_dist = (rays->y_grid - data->playerdata->y_pos + (1 - rays->y_step) / 2) / rays->ray_dir_y;
}

void	update_intersect(t_gamedata *data, t_raydata *rays)
{
    data->intersection.distance = rays->camera_dist;
    data->intersection.x = data->playerdata->x_pos + rays->camera_dist * rays->ray_dir_x;
    data->intersection.y = data->playerdata->y_pos + rays->camera_dist * rays->ray_dir_y;
    data->intersection.side = rays->vertical;
    
    if (rays->vertical)
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

* raycasting con DDA, todas las variables en struct, todavia falta 
 * optimizar, hay problemas con el minimap ahora porque sigue usando bresenham
 * usa una struct local que se inicializa y luego copia data relevante a 
 * data->intersection 

void	cast_ray_2(t_gamedata *data, float ray_angle)
{
	t_raydata rays;
	ft_memset(&rays, 0 , sizeof(t_raydata));
	init_raydata(data, &rays, ray_angle);
	check_collisions(data, &rays);
	update_intersect(data, &rays);
}*/

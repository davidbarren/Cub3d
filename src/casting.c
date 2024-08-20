/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:46:14 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/20 05:20:49 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	get_texture_color(t_image *texture, int x, int y)
{
	int			offset;
	uint32_t	color;

	offset = (y * texture->line_length) + (x * (texture->bpp / 8));
	color = *(uint32_t *)(texture->data_addr + offset);
	return (color);
}

void	render_flor(t_gamedata *data, int wall_bottom, int i)
{
	uint32_t	color;

	color = get_color(data->floor[0], data->floor[1], data->floor[2], 255);
	while (wall_bottom < WINDOW_HEIGHT)
	{
		mlx_put_pixel(data->img, i, wall_bottom, color);
		wall_bottom++;
	}
}

void	render_ceiling(t_gamedata *data, int wall_top, int i)
{
	uint32_t	color;

	color = get_color(data->ceiling[0], data->ceiling[1],
			data->ceiling[2], 255);
	while (wall_top > 0)
	{
		mlx_put_pixel(data->img, i, wall_top, color);
		wall_top--;
	}
}

void	render_walls(t_gamedata *data)
{
	float			ray_angle = data->playerdata->angle - (FOV / 2);
	float			angle_step = FOV / NUM_RAYS;
	int				i;
	int				y;
	float			corrected_distance;
	int				wall_height;
	int				wall_top;
	int				wall_bottom;
	int				tex_x;
	int				tex_y;
	uint32_t		color;
	float			wall_x;
	mlx_texture_t	*texture;

	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(data, ray_angle);
		texture = data->txtrs[data->intersection.direction - 1];
		corrected_distance = data->intersection.distance * cos(data->playerdata->angle - ray_angle);
		wall_height = (int)((WINDOW_HEIGHT / corrected_distance) * WALL_HEIGHT);
		wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
		wall_bottom = wall_top + wall_height;
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom >= WINDOW_HEIGHT)
			wall_bottom = WINDOW_HEIGHT - 1;
		wall_x = fmod(data->intersection.y, 1.0f);
		if (data->intersection.side)
			wall_x = fmod(data->intersection.x, 1.0f);
		//		wall_x = fmod(wall_x + 1.0f, 1.0f);
				if (wall_x > 1.0f)
					wall_x = 1.0f;
				if (wall_x < 0.0f)
					wall_x = 0.0f;
		tex_x = (int)(wall_x * texture->width);
		if (tex_x < 0)
			tex_x = 0;
		if ((uint32_t)tex_x >= texture->width)
			tex_x = texture->width - 1;
		y = wall_top;
		render_ceiling(data, wall_top, i);
		while (y < wall_bottom)
		{
			if (y >= 0 && y < WINDOW_HEIGHT)
			{
				tex_y = (int)((y - wall_top) * (float)texture->height / wall_height);
				if (tex_y < 0)
					tex_y = 0;
				if ((uint32_t)tex_y >= texture->height)
					tex_y = texture->height - 1;
				uint8_t* test = texture->pixels + (tex_y * texture->width + tex_x) * texture->bytes_per_pixel;
				color = get_color(*test, *(test + 1), *(test + 2), *(test + 3));
				//                color = ((uint32_t *)texture->pixels)[tex_y  * texture->width + tex_x];
				mlx_put_pixel(data->img, i, y, color);
			}
			y++;
		}
		render_flor(data, wall_bottom, i);
		i++;
		ray_angle += angle_step;
	}
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
// algoritmo de Bresenham 

void	draw_line(t_gamedata *data, int x1, int y1)
{
	int	color;
	int	err;
	int	e2;

	err = data->line.dx - data->line.dy;
	color = get_color(255, 0, 0, 255);
	while (1)
	{
		mlx_put_pixel(data->img, data->line.x_ray, data->line.y_ray, color);
		if (data->line.x_ray == x1 && data->line.y_ray == y1)
			break ;
		e2 = err * 2;
		if (e2 > -data->line.dy)
		{
			err -= data->line.dy;
			data->line.x_ray += data->line.ray_xdir;
		}
		if (e2 < data->line.dx)
		{
			err += data->line.dx;
			data->line.y_ray += data->line.ray_ydir;
		}
	}
}

void	init_draw_line_param(t_gamedata *data, int inter_x1, int inter_y1)
{
	t_line_params	line;

	line.x_ray = data->playerdata->x_pos * PIXEL_SIZE;
	line.y_ray = data->playerdata->y_pos * PIXEL_SIZE;
	line.dx = ft_abs(inter_x1 - line.x_ray);
	line.dy = ft_abs(inter_y1 - line.y_ray);
	if (line.x_ray < inter_x1)
		line.ray_xdir = 1;
	else
		line.ray_xdir = -1;
	if (line.y_ray < inter_y1)
		line.ray_ydir = 1;
	else
		line.ray_ydir = -1;
	data->line = line;
	draw_line(data, inter_x1, inter_y1);
}

float	get_distan(t_gamedata *data, float ray_x, float ray_y)
{
	return (sqrtf(pow(ray_x - data->playerdata->x_pos, 2) + pow
			(ray_y - data->playerdata->y_pos, 2)));
}
/*
void	cast_ray(t_gamedata *data, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;

	data->intersection.ray_dir_x = cos(ray_angle);
	data->intersection.ray_dir_y = sin(ray_angle);
	ray_x = data->playerdata->x_pos;
	ray_y = data->playerdata->y_pos;
	step_x = cos(ray_angle) * 0.005f;
	step_y = sin(ray_angle) * 0.005f;
	while ((int)ray_x >= 0 && (int)ray_x < MAP_WIDTH && (int)ray_y >= 0 && (int)ray_y < MAP_HEIGHT)
	{
		if (data->map[(int)ray_y][(int)ray_x] == '1')
		{
			data->intersection.x = ray_x;
			data->intersection.y = ray_y;
			data->intersection.distance = get_distan(data, ray_x, ray_y);
			data->intersection.true_ang = atan2(data->intersection.ray_dir_x, data->intersection.ray_dir_y);
//			printf("value of true ang:%f\n", data->intersection.true_ang);
			if (fabs(step_x) > fabs(step_y))
			{
				data->intersection.side = 0; // Pared vertical
				if (data->intersection.ray_dir_y > 0)
				{
//					printf("raydir%f\n", data->intersection.ray_dir_x);
					data->intersection.direction = WEST;
				}
				else
					data->intersection.direction = EAST;
			}
			else if (fabs(step_y) > fabs(step_x))
			{
				data->intersection.side = 1; // Pared horizontal
				if (data->intersection.ray_dir_x > 0)
					data->intersection.direction = NORTH;
				else
					data->intersection.direction = SOUTH;
			}
			return ;
		}
		ray_x += step_x;
		ray_y += step_y;
	}
	data->intersection.x = ray_x;
	data->intersection.y = ray_y;
	data->intersection.distance = MAX_DISTANCE;
}
*/
void cast_ray(t_gamedata *data, float ray_angle) {
    float ray_dir_x = cos(ray_angle);
    float ray_dir_y = sin(ray_angle);

    // Map grid coordinates of the player
    int map_x = (int)data->playerdata->x_pos;
    int map_y = (int)data->playerdata->y_pos;

    // Distance to next x and y side (deltaX, deltaY)
    float delta_dist_x = fabs(1 / ray_dir_x);
    float delta_dist_y = fabs(1 / ray_dir_y);

    // Step direction and initial side distances
    int step_x, step_y;
    float side_dist_x, side_dist_y;

    if (ray_dir_x < 0) {
        step_x = -1;
        side_dist_x = (data->playerdata->x_pos - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - data->playerdata->x_pos) * delta_dist_x;
    }

    if (ray_dir_y < 0) {
        step_y = -1;
        side_dist_y = (data->playerdata->y_pos - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - data->playerdata->y_pos) * delta_dist_y;
    }

    // Perform the DDA
    int hit = 0; // Was there a wall hit?
    int side;    // Was a NS or EW wall hit?
    while (hit == 0) {
        // Jump to the next map square, either in x-direction, or in y-direction
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0; // Vertical wall
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1; // Horizontal wall
        }
        
        // Check if ray has hit a wall
        if (data->map[map_y][map_x] == '1') hit = 1;
    }

    // Calculate the distance projected on the camera direction (Euclidean distance will give a fisheye effect)
    float perp_wall_dist;
    if (side == 0) {
        perp_wall_dist = (map_x - data->playerdata->x_pos + (1 - step_x) / 2) / ray_dir_x;
    } else {
        perp_wall_dist = (map_y - data->playerdata->y_pos + (1 - step_y) / 2) / ray_dir_y;
    }

    // Save intersection data
    data->intersection.distance = perp_wall_dist;
    data->intersection.x = data->playerdata->x_pos + perp_wall_dist * ray_dir_x;
    data->intersection.y = data->playerdata->y_pos + perp_wall_dist * ray_dir_y;
    data->intersection.side = side;
    
    if (side == 0) { // Vertical wall
        if (ray_dir_x > 0)
            data->intersection.direction = WEST;
        else
            data->intersection.direction = EAST;
    } else { // Horizontal wall
        if (ray_dir_y > 0)
            data->intersection.direction = NORTH;
        else
            data->intersection.direction = SOUTH;
    }
}


void cast_rays(t_gamedata *data)
{
	float	ray_angle;
	float	angle_step;
	int		i;

	ray_angle = data->playerdata->angle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(data, ray_angle);
		init_draw_line_param(data, data->intersection.x * PIXEL_SIZE,
			data->intersection.y * PIXEL_SIZE);
		ray_angle += angle_step;
		i++;
	}
}

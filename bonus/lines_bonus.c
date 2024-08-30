/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:05:49 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/30 14:56:48 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	ft_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH)
		return ;
	mlx_put_pixel(img, x, y, color);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

void	draw_line(t_gamedata *data, int x1, int y1)
{
	int	color;
	int	err;
	int	e2;

	err = data->line.dx - data->line.dy;
	color = get_color(255, 0, 0, 255);
	while (1)
	{
		ft_put_pixel(data->img, data->line.x_ray, data->line.y_ray, color);
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

	line.x_ray = data->playerdata->x_pos * data->pixel_size;
	line.y_ray = data->playerdata->y_pos * data->pixel_size;
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

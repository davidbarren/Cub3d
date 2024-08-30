/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:07:40 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/30 12:48:30 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_flor(t_gamedata *data, int wall_bottom, int i)
{
	uint32_t	color;

	color = get_color(data->floor[0], data->floor[1], data->floor[2], 255);
	while (wall_bottom < WINDOW_HEIGHT)
	{
		ft_put_pixel(data->img, i, wall_bottom, color);
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
		ft_put_pixel(data->img, i, wall_top, color);
		wall_top--;
	}
}

void	set_render_parameters(float corrected_distance, t_gamedata *data
		, mlx_texture_t *texture, int i)
{
	int				original_wall_top;
	t_render_params	render;

	ft_memset(&render, 0, sizeof(t_render_params));
	render.wall_height = (int)((WINDOW_HEIGHT / corrected_distance)
			* WALL_HEIGHT);
	render.wall_top = (WINDOW_HEIGHT / 2) - (render.wall_height / 2);
	render.wall_bottom = render.wall_top + render.wall_height;
	original_wall_top = render.wall_top;
	if (render.wall_top < 0)
		render.wall_top = 0;
	if (render.wall_bottom >= WINDOW_HEIGHT)
		render.wall_bottom = WINDOW_HEIGHT - 1;
	render.wall_x = get_wall_x(data);
	render.tex_x = (int)(render.wall_x * texture->width);
	if (render.tex_x < 0)
		render.tex_x = 0;
	if ((uint32_t)render.tex_x >= texture->width)
		render.tex_x = texture->width - 1;
	if (original_wall_top < 0)
		render.y_offset = -original_wall_top;
	render_ceiling(data, render.wall_top, i);
	draw_walls(i, texture, data, &render);
	render_flor(data, render.wall_bottom, i);
}

void	render_walls(t_gamedata *data, mlx_texture_t	*texture)
{
	float			ray_angle;
	float			angle_step;
	int				i;
	float			corrected_distance;

	angle_step = FOV / NUM_RAYS;
	ray_angle = data->playerdata->angle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		dda_new(data, ray_angle);
		texture = data->txtrs[data->intersection.direction - 1];
		corrected_distance = data->intersection.distance
			* cos(data->playerdata->angle - ray_angle);
		set_render_parameters(corrected_distance, data, texture, i);
		i++;
		ray_angle += angle_step;
	}
}

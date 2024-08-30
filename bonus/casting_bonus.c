/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:46:14 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/30 14:55:14 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_walls(int x, mlx_texture_t *texture, t_gamedata *data,
		t_render_params *render)
{
	int			tex_y;
	uint8_t		*test;
	uint32_t	color;
	int			y;

	y = render->wall_top;
	while (y < render->wall_bottom)
	{
		if (y >= 0 && y < WINDOW_HEIGHT)
		{
			tex_y = (int)((y - render->wall_top + render->y_offset)
					* (float)texture->height / render->wall_height);
			if (tex_y < 0)
				tex_y = 0;
			if ((uint32_t)tex_y >= texture->height)
				tex_y = texture->height - 1;
			test = texture->pixels + (tex_y * texture->width + render->tex_x)
				* texture->bytes_per_pixel;
			color = get_color(*test, *(test + 1), *(test + 2), *(test + 3));
			ft_put_pixel(data->img, x, y, color);
		}
		y++;
	}
}

float	get_wall_x(t_gamedata *data)
{
	float	wall_x;

	wall_x = fmod(data->intersection.y, 1.0f);
	if (data->intersection.side)
		wall_x = fmod(data->intersection.x, 1.0f);
	if (wall_x > 1.0f)
		wall_x = 1.0f;
	if (wall_x < 0.0f)
		wall_x = 0.0f;
	return (wall_x);
}

void	cast_rays(t_gamedata *data)
{
	float	ray_angle;
	float	angle_step;
	int		i;

	ray_angle = data->playerdata->angle - (FOV / 2);
	angle_step = FOV / NUM_RAYS;
	i = 0;
	while (i < NUM_RAYS)
	{
		dda_new(data, ray_angle);
		init_draw_line_param(data, data->intersection.x * data->pixel_size,
			data->intersection.y * data->pixel_size);
		ray_angle += angle_step;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 12:46:14 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/19 16:25:50 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t get_texture_color(t_image *texture, int x, int y)
{
    int offset = (y * texture->line_length) + (x * (texture->bpp / 8));
    uint32_t color = *(uint32_t *)(texture->data_addr + offset);
    return color;
} 

void render_flor(t_gamedata *data, int wall_bottom, int i)
{
        while (wall_bottom < WINDOW_HEIGHT) 
        {
            mlx_put_pixel(data->img, i, wall_bottom, get_color(255, 0, 0, 255));
            wall_bottom++;
        }

}

void render_walls(t_gamedata *data) 
{
    float ray_angle = data->playerdata->angle - (FOV / 2);
    float angle_step = FOV / NUM_RAYS;
    int i;
    int y;
    float corrected_distance;
    int wall_height;
    int wall_top;
    int wall_bottom;
    int tex_x;
    int tex_y;
    uint32_t color;
    float wall_x;
    mlx_texture_t *texture = data->este; 

    i = 0;
    while (i < NUM_RAYS) 
    {
        cast_ray(data, ray_angle);
        corrected_distance = data->intersection.distance * cos(data->playerdata->angle - ray_angle);
        wall_height = (int)((WINDOW_HEIGHT / corrected_distance) * WALL_HEIGHT);
        wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
        wall_bottom = wall_top + wall_height;
        if (wall_top < 0) 
            wall_top = 0;
        if (wall_bottom >= WINDOW_HEIGHT) 
            wall_bottom = WINDOW_HEIGHT - 1;
        wall_x = fmod(data->intersection.x, 1.0f);
        tex_x = (int)(wall_x * (int)texture->width);
        if (tex_x < 0) 
            tex_x = 0;
        if ((uint32_t)tex_x >= texture->width) 
            tex_x = texture->width - 1;
        y = wall_top;
        while (y < wall_bottom)
        {
            if (y >= 0 && y < WINDOW_HEIGHT)
            {
                tex_y = (int)((y - wall_top) * (float)texture->height / wall_height);
                if (tex_y < 0) 
                    tex_y = 0;
                if ((uint32_t)tex_y >= texture->height)
                    tex_y = texture->height - 1;
                color = ((uint32_t *)texture->pixels)[tex_y * texture->width + tex_x];
                mlx_put_pixel(data->img, i, y, color);
            }
            y++;
        }
        //render_flor(data, wall_bottom, i);
        i++;
        ray_angle += angle_step;
    }
}

int ft_abs(int n)
{
    if (n < 0)
        return (-n);
    else
        return (n);
}
// algoritmo de Bresenham 
void draw_line(t_gamedata *data, int x1, int y1)
{
	int color;
	int err;
	int e2;

	err = data->line.dx - data->line.dy;
    color = get_color(255, 0, 0, 255);
	while (1)
    {
        mlx_put_pixel(data->img, data->line.x_ray, data->line.y_ray, color);
        if (data->line.x_ray == x1 && data->line.y_ray == y1)
            break;
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

void init_draw_line_param(t_gamedata *data, int inter_x1, int inter_y1) 
{
	t_line_params line;
    
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

float get_distan(t_gamedata *data, float ray_x, float ray_y)
{
	return (sqrtf(pow(ray_x - data->playerdata->x_pos, 2) +
                    	pow(ray_y - data->playerdata->y_pos, 2)));
}

void cast_ray(t_gamedata *data, float ray_angle)
{
    float ray_x;
    float ray_y;
    float step_x;
    float step_y;

    data->intersection.ray_dir_x = cos(ray_angle);
    data->intersection.ray_dir_y = sin(ray_angle);
    ray_x = data->playerdata->x_pos;
    ray_y = data->playerdata->y_pos;
    step_x = cos(ray_angle) * 0.001f;
    step_y = sin(ray_angle) * 0.001f;
    while ((int)ray_x >= 0 && (int)ray_x  < MAP_WIDTH && (int)ray_y >= 0 && (int)ray_y < MAP_HEIGHT)
    {
        if (data->map[(int)ray_y][(int)ray_x ] == '1')
        {
            data->intersection.x = ray_x;
            data->intersection.y = ray_y;
            data->intersection.distance = get_distan(data, ray_x, ray_y);
            if (fabs(step_x) > fabs(step_y))
                data->intersection.side = 0; // Pared vertical
            else
                data->intersection.side = 1; // Pared horizontal
            return ;
        }
        ray_x += step_x;
        ray_y += step_y;
    }
    data->intersection.x = ray_x;
    data->intersection.y = ray_y;
    data->intersection.distance = MAX_DISTANCE;
}


void cast_rays(t_gamedata *data)
{
    float ray_angle;
    float angle_step;
    int i;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/13 16:16:33 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int ft_abs(int n)
{
    if (n < 0)
        return (-n);
    else
        return (n);
}

void draw_line(t_gamedata *data, int x1, int y1) // x1 y y1 son los parametros de interseccion de los rayos  
{
    int color = get_color(255, 0, 0);
    int x_p = data->playerdata->x_pos * PIXEL_SIZE;
    int y_p = data->playerdata->y_pos * PIXEL_SIZE;
    int e2;
    int sx;
    int sy;

    int dx = ft_abs(x1 - x_p);
    int dy = ft_abs(y1 - y_p);
    int err = dx - dy;

    // Determinar la dirección de incremento para x_p
    if (x_p < x1)
        sx = 1;
    else
        sx = -1;

    // Determinar la dirección de incremento para y_p
    if (y_p < y1)
        sy = 1;
    else
        sy = -1;

    while (1)
    {
        mlx_put_pixel(data->img, x_p, y_p, color);

        if (x_p == x1 && y_p == y1)
            break;

        e2 = err * 2;

        if (e2 > -dy)
        {
            err -= dy;
            x_p += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y_p += sy;
        }
    }
}

t_intersection cast_ray(t_gamedata *data, float ray_angle)
{
    float step_size = 0.08f; // Tamaño del paso para el rayo 
    float ray_x = data->playerdata->x_pos;
    float ray_y = data->playerdata->y_pos;

    while (1)
    {
        ray_x += cos(ray_angle) * step_size;
        ray_y += sin(ray_angle) * step_size;

        int map_x = (int)ray_x;
        int map_y = (int)ray_y;
        if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
        {
            t_intersection intersection;
            intersection.x = ray_x;
            intersection.y = ray_y;
            intersection.distance = MAX_DISTANCE;
            return intersection;
        }
        if (data->map[map_y][map_x] == '1')
        {
            t_intersection intersection;
            intersection.x = ray_x;
            intersection.y = ray_y;
            intersection.distance = sqrtf(pow(ray_x - data->playerdata->x_pos, 2) +
                                          pow(ray_y - data->playerdata->y_pos, 2));
            return intersection;
        }
    }
}


void cast_rays(t_gamedata *data)
{
    float ray_angle;
    float angle_step = FOV / NUM_RAYS;
    int i;

    ray_angle = data->playerdata->angle - (FOV / 2); // Comienza en el ángulo izquierdo

    i = 0;
    while (i < NUM_RAYS)
    {
        t_intersection intersection = cast_ray(data, ray_angle);   
        draw_line(data, intersection.x * PIXEL_SIZE, intersection.y * PIXEL_SIZE);    
        ray_angle += angle_step;
        i++;
    }
}

void initializePlayer(t_gamedata *data, char **map)
{
	t_player *player;

	player = data->playerdata;
    if (map[(int)player->y_pos][(int)player->x_pos] == 'N')
	{
        player->angle = 3 * PI / 2; // Mirando hacia arriba (270 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'S')
	{
        player->angle = PI / 2; // Mirando hacia abajo (90 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'E')
	{
        player->angle = 0; // Mirando hacia derecha (90 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'W')
	{
        player->angle = PI; // Mirando hacia izquierda (90 grados)
        return ;
	}
}

void moving(t_gamedata *data, int direction)
{
    t_player *player = data->playerdata;
    float move_x = direction * MOVE_SPEED * cos(player->angle);
    float move_y = direction * MOVE_SPEED * sin(player->angle);

    float new_x = player->x_pos + move_x;
    float new_y = player->y_pos + move_y;

    // Ajuste del margen de colisión
    int map_x;
    int map_y;

    if (move_x > 0)
        map_x = (int)(new_x + COLLISION_MARGIN);
    else
        map_x = (int)(new_x - COLLISION_MARGIN);

    if (move_y > 0)
        map_y = (int)(new_y + COLLISION_MARGIN);
    else
        map_y = (int)(new_y - COLLISION_MARGIN);

    if (data->map[map_y][map_x] == '1')
        return;

    player->x_pos = new_x;
    player->y_pos = new_y;
}

void moving_side(t_gamedata *data, int direction)
{
    t_player *player = data->playerdata;
    float move_x = direction * MOVE_SPEED * cos(player->angle + (PI / 2));
    float move_y = direction * MOVE_SPEED * sin(player->angle + (PI / 2));

    float new_x = player->x_pos + move_x;
    float new_y = player->y_pos + move_y;

    // Ajuste del margen de colisión
    int map_x;
    int map_y;

    if (move_x > 0)
        map_x = (int)(new_x + COLLISION_MARGIN);
    else
        map_x = (int)(new_x - COLLISION_MARGIN);

    if (move_y > 0)
        map_y = (int)(new_y + COLLISION_MARGIN);
    else
        map_y = (int)(new_y - COLLISION_MARGIN);

    if (data->map[map_y][map_x] == '1')
        return; 

    player->x_pos = new_x;
    player->y_pos = new_y;
}

void turnPlayer(t_gamedata *data, int direction)
{
	t_player *player;

	player = data->playerdata;
    player->angle += direction * TURN_SPEED;
    if (player->angle < 0)
	{
        player->angle += 2 * PI;
    } 
	else if (player->angle >= 2 * PI) 
	{
        player->angle -= 2 * PI;
    }
	printf("angle %f\n", player->angle);
}
uint32_t	get_color(uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t alpha;
	
	alpha = 255; 
	return (red << 24) | (green << 16) | (blue << 8) | alpha;
}


void    ft_player(t_gamedata *data)
{

	uint32_t color;
 	int player_size;
    int centerX;
    int centerY;

	player_size = PIXEL_SIZE / 2;
	centerX =  PIXEL_SIZE * data->playerdata->x_pos; //+ player_size;
	centerY =  PIXEL_SIZE * data->playerdata->y_pos; //+ player_size;
	color = get_color (data->ceiling[0] , data->ceiling[1], data->ceiling[2]);
	int i = -player_size / 2;
	while (i < player_size / 3) 
	{
    	int j = -player_size / 3;
    	while (j < player_size / 3) 
		{
        	mlx_put_pixel(data->img, centerX + j, centerY + i, color);
        	++j;
    	}
    	++i;
	}
}
void display_map(t_gamedata *data)
{
	int x;
	int y;
	int i;
	int i2;
	uint32_t color;

	y = 0;
	color = get_color(data->floor[0], data->floor[1], data->floor[2]);
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] == '1')
			{
				i = 0;
				while (i < PIXEL_SIZE)
				{
					i2 = 0;
					while(i2 < PIXEL_SIZE)
					{
						mlx_put_pixel(data->img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + i2, color);
						i2++;
					}
				i++;
				}
			}
			x++;
		}
		y++;
	}

    ft_player(data);
}



void my_keyhook(void* param)
{
    t_gamedata *data;

    data = param;
    ft_memset(data->img->pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
    if (mlx_is_key_down(data->window, MLX_KEY_W))
        moving(data, 1);
    if (mlx_is_key_down(data->window, MLX_KEY_S))
        moving(data, -1);
    if (mlx_is_key_down(data->window, MLX_KEY_A))
        moving_side(data, -1);
    if (mlx_is_key_down(data->window, MLX_KEY_D))
        moving_side(data, + 1);
    if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
        turnPlayer(data, -1);
    if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
        turnPlayer(data, 1);
    
    display_map(data);
    cast_rays(data);
    
    if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
        mlx_close_window(data->window);
}


void	init_gamestate(t_gamedata *data)
{
	data->c = 0;
    data->playerdata->x_pos += 0.5;
    data->playerdata->y_pos += 0.5;
 	data->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	data->img = mlx_new_image(data->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	initializePlayer(data, data->map);
	mlx_image_to_window(data->window, data->img, 0, 0);
	display_map(data);
	mlx_loop_hook(data->window, my_keyhook, data);
	//mlx_key_hook(data->window, &my_keyhook, data);
    mlx_loop(data->window);
    mlx_close_window(data->window);
    mlx_terminate(data->window);
    free_data_content(data);
    free(data); 
    printf("end of game :)\n");
}

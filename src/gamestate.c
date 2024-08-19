/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/19 22:05:44 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void moving_forward_backward(t_gamedata *data, int direction)
{
    t_player *player;
    int map_x;
    int map_y;
    float move_x;
    float move_y;

    player = data->playerdata;
    move_x = direction * MOVE_SPEED * cos(player->angle);
    move_y = direction * MOVE_SPEED * sin(player->angle);
    if (move_x > 0)
        map_x = (int)((player->x_pos + move_x) + COLLISION_MARGIN);
    else
        map_x = (int)((player->x_pos + move_x) - COLLISION_MARGIN);
    if (move_y > 0)
        map_y = (int)((player->y_pos + move_y) + COLLISION_MARGIN);
    else
        map_y = (int)((player->y_pos + move_y) - COLLISION_MARGIN);
    if (data->map[map_y][map_x] == '1')
        return;
    player->x_pos += move_x;
    player->y_pos += move_y;
}

void moving_side(t_gamedata *data, int direction)
{
    t_player *player;
    int map_x;
    int map_y;
    float move_x;
    float move_y;

    player = data->playerdata;
    move_x = direction * MOVE_SPEED * cos(player->angle + (PI / 2));
    move_y = direction * MOVE_SPEED * sin(player->angle + (PI / 2));
    if (move_x > 0)
        map_x = (int)((player->x_pos + move_x) + COLLISION_MARGIN);
    else
        map_x = (int)((player->x_pos + move_x) - COLLISION_MARGIN);
    if (move_y > 0)
        map_y = (int)((player->y_pos + move_y) + COLLISION_MARGIN);
    else
        map_y = (int)((player->y_pos + move_y) - COLLISION_MARGIN);
    if (data->map[map_y][map_x] == '1')
        return;
    player->x_pos += move_x;
    player->y_pos += move_y;
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
}
uint32_t	get_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return (red << 24) | (green << 16) | (blue << 8) | alpha;
}


void    ft_player(t_gamedata *data)
{

	uint32_t color;
 	int player_size;
    int centerX;
    int centerY;

	player_size = PIXEL_SIZE / 2;
	centerX =  PIXEL_SIZE * data->playerdata->x_pos;
	centerY =  PIXEL_SIZE * data->playerdata->y_pos;
	color = get_color(0, 0, 255, 255);
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
void draw_flor(t_gamedata *data)
{
    int x;
	int y;
	int i;
	int i2;
	uint32_t color;

	y = 0;
	color = get_color(255, 255, 255, 255); //white color
	while (data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			if (data->map[y][x] != '1' && data->map[y][x] != ' ' && data->map[y][x] != '\t')
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
}
void display_map(t_gamedata *data)
{
	int x;
	int y;
	int i;
	int i2;
	uint32_t color;

	y = 0;
	color = get_color(0,0,0, 255);
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
    draw_flor(data);
    ft_player(data);
}


void my_keyhook(void* param)
{
    t_gamedata *data;

    data = param;
    ft_memset(data->img->pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
    if (mlx_is_key_down(data->window, MLX_KEY_W))
        moving_forward_backward(data, 1);
    if (mlx_is_key_down(data->window, MLX_KEY_S))
        moving_forward_backward(data, -1);
    if (mlx_is_key_down(data->window, MLX_KEY_A))
        moving_side(data, -1);
    if (mlx_is_key_down(data->window, MLX_KEY_D))
        moving_side(data, + 1);
    if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
        turnPlayer(data, -1);
    if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
    {   turnPlayer(data, 1);   }
	render_walls(data);
	display_map(data);
    cast_rays(data);
    if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
    {    mlx_close_window(data->window);}
	
}


void	init_gamestate(t_gamedata *data)
{
 	data->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	data->img = mlx_new_image(data->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	initializePlayer(data, data->map);
	load_texture(data);
	mlx_image_to_window(data->window, data->img, 0, 0);
	display_map(data);
//	load_texture(data);
	mlx_loop_hook(data->window, my_keyhook, data);
    mlx_loop(data->window);
    mlx_close_window(data->window);
    mlx_terminate(data->window);
    free_data_content(data);
    free(data); 
    printf("end of game :)\n");
}

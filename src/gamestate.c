/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/25 18:00:07 by dzurita          ###   ########.fr       */
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
/* 		player->x_pos = 0.5;
		player->y_pos = 0.5; */
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
	t_player *player;

	float t1;
	float t2;

	player = data->playerdata;
	printf("x %f y %f angle %f c= %d\n", player->x_pos, player->y_pos, player->angle, data->c);
	printf("type int x %d y %d angle %f c= %d\n", (int)player->x_pos, (int)player->y_pos, player->angle, data->c);
    float new_x = player->x_pos + direction * MOVE_SPEED * sin(player->angle);
    float new_y = player->y_pos + direction * MOVE_SPEED * cos(player->angle);

	if (direction < 0)
	{
	t1 = 0.4 + new_x;
	t2 = 0.4 + new_y;
	}
	else
	{
	t1 = -0.1 + new_x;
	t2 = 0.3 + new_y;
	}
	printf("map %c\n", data->map[(int)t2][(int)t1]);
	if (data->map[(int)(t2)][(int)(t1)] ==  '1')
		return ;
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
}
uint32_t	get_color(uint8_t red, uint8_t green, uint8_t blue)
{
	// Componentes de color
	//red
	//green
	//blue
	uint8_t alpha;
	
	alpha = 255;   // Máximo para opacidad
	// Combinar los componentes
	return (red << 24) | (green << 16) | (blue << 8) | alpha;
	//return (color);
}


void    ft_player(t_gamedata *data)
{

	uint32_t color;
 	int player_size;
    float centerX;
    float centerY;

	player_size = 10;
	centerX =  (float)PIXEL_SIZE * data->playerdata->x_pos + (float)player_size;
	centerY =  (float)PIXEL_SIZE * data->playerdata->y_pos + (float)player_size;
	color = get_color (data->ceiling[0] , data->ceiling[1], data->ceiling[2]);
	int i = -player_size / 2;
	while (i < player_size / 2) 
	{
    	int j = -player_size / 2;
    	while (j < player_size / 2) 
		{
        	mlx_put_pixel(data->img, centerX + j, centerY + i, color);
        	++j;
    	}
    	++i;
	}
}
void	display_map(t_gamedata *data)
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
	if (mlx_is_key_down(data->window, MLX_KEY_W ))
        moving(data, 1);
   	if (mlx_is_key_down(data->window, MLX_KEY_S))
        moving(data, -1);
	if (mlx_is_key_down(data->window, MLX_KEY_A))
		turnPlayer(data, 1);
	if (mlx_is_key_down(data->window, MLX_KEY_D))
        turnPlayer(data, -1);  
	display_map(data);
	if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
		mlx_close_window(data->window);

}

void	init_gamestate(t_gamedata *data)
{
	data->c = 0;
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

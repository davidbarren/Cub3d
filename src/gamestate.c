/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/24 17:52:20 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void initializePlayer(t_gamedata *data, char **map)
{
	t_player *player;

	player = data->playerdata;
    if (map[(int)player->y_pos][(int)player->x_pos] == 'N')
	{
		player->x_pos += 0.5;
        player->y_pos += 0.5;
        player->angle = 3 * PI / 2; // Mirando hacia arriba (270 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'S')
	{
		player->x_pos += 0.6;
        player->y_pos += 0.6;
        player->angle = PI / 2; // Mirando hacia abajo (90 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'E')
	{
		player->x_pos += 0.6;
        player->y_pos += 0.6;
        player->angle = 0; // Mirando hacia abajo (90 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'W')
	{
		player->x_pos += 0.5;
        player->y_pos += 0.5;
        player->angle = PI; // Mirando hacia abajo (90 grados)
        return ;
	}
}

void moving(t_gamedata *data, int direction)
{
	t_player *player;

	player = data->playerdata;
	printf("x %f y %f angle %f c= %d\n", player->x_pos, player->y_pos, player->angle, data->c);
	data->c++;
/* 	if (direction ==  -1 && data->map[(int)player->y_pos - 1][(int)player->x_pos] == '1')
        return ;
	if (direction ==  1 && data->map[(int)player->y_pos + 1][(int)player->x_pos] == '1')
        return ; */
    float new_x = player->x_pos + direction * MOVE_SPEED * sin(player->angle);
    float new_y = player->y_pos + direction * MOVE_SPEED * cos(player->angle);
  /*   if (data->map[(int)newY][(int)newX] == '0') 
	{*/
		//printf("hola\n"); 
        player->x_pos = new_x;
        player->y_pos = new_y;
   // }
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

void	move_left(t_gamedata *content)
{
	t_player	*player;

	player = content->playerdata;
	if (content->map[(int)player->y_pos][(int)player->x_pos - 1] == '1')
        return ;
	else
    { 
		turnPlayer(content, -1);
		printf("letf %f\n", player->angle);
        //content->player->instances[0].x -= player->x_pos;
    }
}

void	move_right(t_gamedata *content)
{
	t_player *player;

	player = content->playerdata;
    if (content->map[(int)player->y_pos][(int)player->x_pos + 1] == '1')
        return ;
    else
    {
        turnPlayer(content, 1);
		printf("right %f\n", player->angle); 
        //content->player->instances[0].x += player->x_pos;
    }
    //printf("x: %d\n", content->x);
}
void    move_up(t_gamedata *content)
{
	t_player *player;

	//movePlayer(content, -1);
	player = content->playerdata;
    if (content->map[(int)player->y_pos - 1][(int)player->x_pos] == '1')
        return ;
    else
    {   
		//movePlayer(content, -1);
		printf("normal %f  %f\n", player->y_pos, player->x_pos);
		printf("intances %d  %d\n", content->player->instances[0].y, content->player->instances[0].x);
		//printf("down %d  %d\n", content->player->instances[0].x, content->player->instances[0].y);
        //content->player->instances[0].z = player->angle;
		//content->player->instances[0].x = player->x_pos;
        content->player->instances[0].y -= (int)player->y_pos;
        //player->y_pos -= 1;
    }
    //printf("y: %d\n", content->y);
}
void    move_down(t_gamedata *content)
{
	t_player *player;

	//movePlayer(content, 1);
	player = content->playerdata;
    if (content->map[(int)player->y_pos + 1][(int)player->x_pos] == '1')
        return ;
    else
    {  
		//movePlayer(content, 1); 
		printf("normal %f  %f\n", player->y_pos, player->x_pos);
		printf("intances %d  %d\n", content->player->instances[0].y, content->player->instances[0].x);;
        //content->player->instances[0].z = player->angle;
		//content->player->instances[0].x = player->x_pos;
        content->player->instances[0].y += (int)player->y_pos;
        //player->y_pos += 1;
    }
   //printf("y: %d\n", content->y);
}
void	move_player(t_gamedata *data)
{
	
    if (mlx_is_key_down(data->window, MLX_KEY_W ))
        moving(data, -1);
   	else if (mlx_is_key_down(data->window, MLX_KEY_S))
        moving(data, 1);
	else if (mlx_is_key_down(data->window, MLX_KEY_A))
		turnPlayer(data, -1);
	else if (mlx_is_key_down(data->window, MLX_KEY_D))
        turnPlayer(data, 1);  
}


void    ft_player(t_gamedata *data, int x, int y)
{
 		// Componentes de color
uint8_t red = 255;     // Máximo para rojo
uint8_t green = 0;     // Mínimo para verde
uint8_t blue = 0;      // Mínimo para azul
uint8_t alpha = 255;   // Máximo para opacidad

// Combinar los componentes
uint32_t color = (red << 24) | (green << 16) | (blue << 8) | alpha;

 	int player_size;
    int centerX;
    int centerY;

	player_size = PIXEL_SIZE / 4;
	centerX = x * PIXEL_SIZE + PIXEL_SIZE / 2;
	centerY = y * PIXEL_SIZE + PIXEL_SIZE / 2;
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
  

/*  	content->texture = mlx_load_png("rojo.png");
    // chequear por    error(); 
	content->player = mlx_texture_to_image(content->window, content->texture);
   // chequear por    error(); 
	mlx_resize_image(content->player, PIXEL_SIZE / 4, PIXEL_SIZE / 4);
	   // chequear por    error(); 
	mlx_image_to_window(content->window, content->player, x * PIXEL_SIZE + 3, y * PIXEL_SIZE + 2);
   // chequear por    error();
   		printf("normal %f  %f\n", content->playerdata->y_pos, content->playerdata->x_pos);
		printf("intances %d  %d\n", content->player->instances[0].y, content->player->instances[0].x);*/
}
void	display_map(t_gamedata *data)
{
	int x;
	int y;
	int i;
	int i2;
	

	y = 0;
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
						mlx_put_pixel(data->img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + i2, 255);
						i2++;
					}
				i++;
				}
			}
			x++;
		}
		y++;
	}
	ft_player(data, data->playerdata->x_pos, data->playerdata->y_pos);
}

void my_keyhook(void* param)
{
    
    t_gamedata *data;

    data = param;

	ft_memset(data->img->pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
	move_player(data);
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
	mlx_loop_hook(data->window, my_keyhook, data);
	//mlx_key_hook(data->window, &my_keyhook, data);
    mlx_loop(data->window);
    mlx_close_window(data->window);
    mlx_terminate(data->window);
    free_data_content(data);
    free(data); 
    printf("end of game :)\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/22 16:34:43 by dzurita          ###   ########.fr       */
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
		player->x_pos += 0.5;
        player->y_pos += 0.5;
        player->angle = 0; // Mirando hacia abajo (90 grados)
        return ;
	}
	if (map[(int)player->y_pos][(int)player->x_pos] == 'E')
	{
		player->x_pos += 0.5;
        player->y_pos += 0.5;
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

void movePlayer(t_gamedata *data, int direction)
{
	t_player *player;

	player = data->playerdata;
    float newX = player->x_pos + direction * MOVE_SPEED * cos(player->angle);
    float newY = player->y_pos + direction * MOVE_SPEED * sin(player->angle);
    /* if (map[(int)newY][(int)newX] == '0') 
	{
		printf("hola\n"); */
        player->x_pos = newX;
        player->y_pos = newY;
    //}
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

	player = content->playerdata;
    if (content->map[(int)player->y_pos - 1][(int)player->x_pos] == '1')
        return ;
    else
    {   
		movePlayer(content, 1);
		//printf("up %f  %f\n", player->y_pos, player->x_pos);
		printf("down %d  %d\n", content->player->instances[0].x, content->player->instances[0].z);
        //content->player->instances[0].z = player->angle;
		//content->player->instances[0].x = player->x_pos;
        content->player->instances[0].y -= player->y_pos;
        //player->y_pos -= 1;
    }
    //printf("y: %d\n", content->y);
}
void    move_down(t_gamedata *content)
{
	t_player *player;

	player = content->playerdata;
    if (content->map[(int)player->y_pos + 1][(int)player->x_pos] == '1')
        return ;
    else
    {  
		movePlayer(content, -1); 
		printf("down %d  %d\n", content->player->instances[0].x, content->player->instances[0].z);
        //content->player->instances[0].z = player->angle;
		//content->player->instances[0].x = player->x_pos;
        content->player->instances[0].y += player->y_pos;
        //player->y_pos += 1;
    }
   //printf("y: %d\n", content->y);
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
    
    t_gamedata *content;

    content = param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(content->window);
    else if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
        move_up(content);
 	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        move_down(content);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(content);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        move_right(content);
}

void    ft_player(mlx_t* mlx, t_gamedata *content, int x, int y)
{
    content->texture = mlx_load_png("rojo.png");
    // chequear por    error(); 
	content->player = mlx_texture_to_image(mlx, content->texture);
   // chequear por    error(); 
	mlx_resize_image(content->player, PIXEL_SIZE / 4, PIXEL_SIZE / 4);
	   // chequear por    error(); 
	mlx_image_to_window(mlx, content->player, x * PIXEL_SIZE + 3, y * PIXEL_SIZE + 2);
   // chequear por    error(); 
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
						mlx_put_pixel(data->img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + i2, data->floor[0]);
						i2++;
					}
				i++;
				}
			}
			x++;
		}
		y++;
	}
    ft_player(data->window, data, data->playerdata->x_pos, data->playerdata->y_pos);
}

void	init_gamestate(t_gamedata *data)
{
	data->x_pos = 5;//just for test with the map Sample
	data->y_pos = 9;//
	initializePlayer(data, data->map);
 	data->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", false);
	data->img = mlx_new_image(data->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	display_map(data);
    mlx_image_to_window(data->window, data->img, 0, 0);
	mlx_key_hook(data->window, &my_keyhook, data);
    mlx_loop(data->window);
    mlx_close_window(data->window);
    mlx_terminate(data->window);
    free_data_content(data);
    free(data); 
    printf("end of game :)\n");
}

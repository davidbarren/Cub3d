/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/18 17:08:54 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    move_left(t_gamedata *content)
{
    if (content->map[content->y_pos][content->x_pos - 1] == '1'
	|| ft_is_whitespace(content->map[content->y_pos][content->x_pos - 1]) == 1)
        return ;
    else
    {   
        content->player->instances[0].x -= PIXEL_SIZE;
        content->x_pos -= 1;
    }
}

void    move_right(t_gamedata *content)
{
    if (content->map[content->y_pos][content->x_pos + 1] == '1'
	|| ft_is_whitespace(content->map[content->y_pos][content->x_pos + 1]) == 1)
        return ;
    else
    {
        content->x_pos += 1;
        content->player->instances[0].x += PIXEL_SIZE;
    }
    //printf("x: %d\n", content->x);
}
void    move_up(t_gamedata *content)
{
    if (content->map[content->y_pos - 1][content->x_pos] == '1'
	|| ft_is_whitespace(content->map[content->y_pos - 1][content->x_pos]) == 1)
        return ;
    else
    {   
        content->player->instances[0].y -= PIXEL_SIZE;;
        content->y_pos -= 1;
    }
    //printf("y: %d\n", content->y);
}
void    move_down(t_gamedata *content)
{
    if (content->map[content->y_pos + 1][content->x_pos] == '1'
	|| ft_is_whitespace(content->map[content->y_pos + 1][content->x_pos]) == 1)
        return ;
    else
    {   
        content->player->instances[0].y += PIXEL_SIZE;;
        content->y_pos += 1;
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
	mlx_resize_image(content->player, 20, 20);
	   // chequear por    error(); 
	mlx_image_to_window(mlx, content->player, x * 53, y * 52);
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
			if (data->map[y][x] == '1' || ft_is_whitespace(data->map[y][x]) == 1)
			{
				i = 0;
				while (i <= PIXEL_SIZE)
				{
					i2 = 0;
					while(i2 <= PIXEL_SIZE)
					{
						mlx_put_pixel(data->img, x * PIXEL_SIZE + i, y * PIXEL_SIZE + i2, data->floor[0]);
						i2++;
					}
				i++;
				}
			}
            if (data->map[y][x] == 'N')
				ft_player(data->window, data, x, y);
			x++;
		}
		y++;
	}
}

void	init_gamestate(t_gamedata *data)
{
	data->x_pos = 5;//just for test with the map Sample
	data->y_pos = 9;//
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

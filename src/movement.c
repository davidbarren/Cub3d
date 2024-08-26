/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:58:41 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/27 01:03:30 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	moving_forward_backward(t_gamedata *data, int direction)
{
	t_player	*player;
	int			map_x;
	int			map_y;
	float		move_x;
	float		move_y;

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
		return ;
	player->x_pos += move_x;
	player->y_pos += move_y;
}

void	moving_side(t_gamedata *data, int direction)
{
	t_player	*player;
	int			map_x;
	int			map_y;
	float		move_x;
	float		move_y;

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
		return ;
	player->x_pos += move_x;
	player->y_pos += move_y;
}

void	turn_player(t_gamedata *data, int direction)
{
	t_player	*player;

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

void	mouse_move_hook(double xpos, double ypos, void *param)
{
	t_gamedata		*data;
	static double	last_x = 0.0;
	double			delta_x;
//	double delta_y;
	(void) ypos;
	data = (t_gamedata *)param;
//	delta_y = ypos;
	delta_x = xpos - last_x;
	if (delta_x < 0)
		turn_player(data, -1);
	else if (delta_x > 0)
		turn_player(data, 1);
	last_x = xpos;
}

void	cub3d_keyhook(void *param)
{
	t_gamedata	*data;

	data = param;
	ft_memset(data->img->pixels, 0, WINDOW_WIDTH * WINDOW_HEIGHT * 4);
	if (mlx_is_key_down(data->window, MLX_KEY_W))
		moving_forward_backward(data, 1);
	if (mlx_is_key_down(data->window, MLX_KEY_S))
		moving_forward_backward(data, -1);
	if (mlx_is_key_down(data->window, MLX_KEY_A))
		moving_side(data, -1);
	if (mlx_is_key_down(data->window, MLX_KEY_D))
		moving_side(data, 1);
	if (mlx_is_key_down(data->window, MLX_KEY_LEFT))
		turn_player(data, -1);
	if (mlx_is_key_down(data->window, MLX_KEY_RIGHT))
		turn_player(data, 1);
	render_walls(data, NULL);
	display_map(data);
	cast_rays(data);
	if (mlx_is_key_down(data->window, MLX_KEY_ESCAPE))
		mlx_close_window(data->window);
}
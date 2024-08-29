/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curso_mouse_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:58:41 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 16:14:37 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	mouse_move_hook(double xpos, double ypos, void *param)
{
	t_gamedata		*data;
	static double	last_x = 0.0;
	double			delta_x;

	(void) ypos;
	data = (t_gamedata *)param;
	delta_x = xpos - last_x;
	if (delta_x < 0)
		turn_player(data, -1, TURN_SPEED_MOUSE);
	else if (delta_x > 0)
		turn_player(data, 1, TURN_SPEED_MOUSE);
	last_x = WINDOW_WIDTH / 2.0;
	mlx_set_cursor_mode(data->window, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->window, WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
}
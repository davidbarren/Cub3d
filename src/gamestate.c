/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamestate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:36:06 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/15 12:51:42 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_gamestate(t_gamedata *data)
{
	data->window = mlx_init(WINDOW_HEIGHT, WINDOW_WIDTH, "Cub3d", false);
	mlx_loop(data->window);
	mlx_close_window(data->window);
	mlx_terminate(data->window);
	free_data_content(data);
	free(data);
	printf("end of game :)\n");
}

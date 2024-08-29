/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:12 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/29 16:16:06 by dzurita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

uint32_t	get_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return ((uint32_t)red << 24
		|(uint32_t)green << 16
		|(uint32_t)blue << 8
		|(uint32_t)alpha);
}

int	main(int argc, char **argv)
{
	t_file		filedata;
	t_gamedata	*data;

	file_validation(&filedata, argc, argv);
	scene_opening(&filedata);
	data = scene_parsing(&filedata);
	init_gamestate(data);
	return (0);
}

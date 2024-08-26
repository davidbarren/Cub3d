/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:12 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/27 01:05:01 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

uint32_t	get_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:12 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/11 17:37:30 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_file	filedata;

	file_validation(&filedata, argc, argv);
	scene_opening(&filedata);
	scene_parsing(&filedata);
	return (0);
}

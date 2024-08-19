/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 19:45:48 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/19 22:25:15 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_txtrs(t_gamedata *data)
{
//	data->txtrs = ft_calloc(4, sizeof(mlx_texture_t *));
//	data->txtrs[0] = ft_calloc(1, sizeof(mlx_texture_t));
//	data->txtrs[1] = ft_calloc(1, sizeof(mlx_texture_t));
//	data->txtrs[2] = ft_calloc(1, sizeof(mlx_texture_t));
//	data->txtrs[3] = ft_calloc(1, sizeof(mlx_texture_t));
	load_texture(data);
}


void	load_texture(t_gamedata *data)
{
	data->txtrs[0] = mlx_load_png(data->paths->north);//oeste
    if (!data->txtrs[0])
    {
		ft_printerror("error loading north texture\n");
        error_free(BAD_LOADING, data, NULL);
    }
	data->txtrs[1] = mlx_load_png(data->paths->east);
	if (!data->txtrs[1])
	{
		ft_printerror("error loading east texture\n");
		error_free(BAD_LOADING, data, NULL);
	}
	data->txtrs[2] = mlx_load_png(data->paths->south);
	if (!data->txtrs[2])
	{
		ft_printerror("error loading south texture\n");
		error_free(BAD_LOADING, data, NULL);
	}
	data->txtrs[3] = mlx_load_png(data->paths->west);
    if (!data->txtrs[3])
    {
		ft_printerror("error loading north texture\n");
        error_free(BAD_LOADING, data, NULL);
    }
}


void	delete_textures(t_gamedata *data)
{
	if (data->txtrs[0])
		mlx_delete_texture(data->txtrs[0]);
	if (data->txtrs[1])
		mlx_delete_texture(data->txtrs[1]);
	if (data->txtrs[2])
		mlx_delete_texture(data->txtrs[2]);
	if (data->txtrs[3])
		mlx_delete_texture(data->txtrs[3]);
}

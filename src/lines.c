/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:05:49 by dbarrene          #+#    #+#             */
/*   Updated: 2024/08/30 14:48:05 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH)
		return ;
	mlx_put_pixel(img, x, y, color);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

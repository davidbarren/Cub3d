/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:24:44 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/15 11:08:06 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_is_whitespace(char c)
{
	if (c == 9 || c == 32)
		return (1);
	if (c >= 11 && c <= 13)
		return (1);
	return (0);
}

int	ft_atoi_rgb(char *str)
{
	int	result;

	result = 0;
	while (ft_is_whitespace(*str))
		str++;
	if (*str == '-')
		return (-1);
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str - '0');
		str++;
		if (result > 255)
			return (-1);
	}
	while (*str && ft_is_whitespace(*str))
		str++;
	if (*str)
		return (-1);
	return (result);
}

char	*ft_strtok(char *str, char delim)
{
	static char	*ptr;
	char		*token;

	if (!str)
		token = ptr;
	if (str)
	{
		ptr = str;
		token = ptr;
	}
	if (!ptr || !*ptr)
		return (NULL);
	while (*ptr && *ptr != delim)
		ptr++;
	if (*ptr)
	{
		*ptr = 0;
		ptr++;
	}
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:00:25 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/15 05:29:47 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_border(char *line)
{
	if (!line)
		return (0);
	if (line[0] == '\n')
		return (0);
	while (*line)
	{
		if (*line != '1' && *line != ' ' && *line != '\n') 
			return (0);
		line++;
	}
	return (1);
}

void	ft_skip_spaces(char **str)
{
	while (**str && (**str == ' ' || **str == '\t' || **str == '\v'))
		*str += 1;
}

void	load_paths(t_file *scenedata, t_paths *paths)
{
	char	**scene;
	char	*temp;
	int		i;

	i = 0;
	scene = scenedata->scene_data;
	while (scene[i] && !is_border(scene[i]))
	{
		temp = scene[i];
		ft_skip_spaces(&temp);
		if (!ft_strncmp(temp, "NO", 2))
			paths->north_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "SO", 2))
			paths->south_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "WE", 2))
			paths->west_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "EA", 2))
			paths->east_path = ft_strdup(ft_strchr(temp, '.'));
		else if (!ft_strncmp(temp, "C", 1))
			paths->ceiling_colorscheme = ft_strdup(temp);
		else if (!ft_strncmp(temp, "F", 1))
			paths->floor_colorscheme = ft_strdup(temp);
		i++;
	}
	scenedata->map_index = i;
//	printf("index where map begins:%d\n", i);
}

int	ft_is_whitespace(char c)
{
	if (c == 9 || c == 32)
		return (1);
	if (c >= 11 && c <= 13 )
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
	static char *ptr;
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


int	load_colorschemes(char *str, unsigned char *target)
{
	char	*temp;
	int		i;
	int		result;
	char	*token;

	i = 0;
	temp = str;
	printf("in load colors:%s\n", temp);
	while (*temp && (ft_is_whitespace(*temp) || *temp == 'F' || *temp == 'C' ))
		temp++;
	token = ft_strtok(temp, ',');
	while (token && i < 3)
	{
		result = ft_atoi_rgb(token);
		printf("result:%d\n", result);
		if (result < 0)
			return (BAD_RGB);
		target[i] = result;
		token = ft_strtok(NULL, ',');
		i++;
	}
	if (token || i != 3)
		return (BAD_RGB);
	return (0);
}

void	print_colorschemes(t_gamedata *data)
{
	printf("floor colorschemes in R G B:\n");
	printf("R:%d\nG:%d\nB:%d\n",
			data->floor[0], data->floor[1], data->floor[2]);
	printf("ceiling colorschemes in R G B:\n");
	printf("R:%d\nG:%d\nB:%d\n",
			data->ceiling[0], data->ceiling[1], data->ceiling[2]);
}
/*
	TODO:
increment pointer to skip non-digits
make ft_strtok and split by commas
if not 3 tokens then return error
change atoi so that it returns error whenever it encounters nondigit since
tokens that are only  digits are passed to it

*/
void	scene_parsing(t_file *scenedata)
{
	t_gamedata	*data;
	t_paths		*paths;	

	data = ft_calloc (1, sizeof(t_gamedata));
	paths = ft_calloc (1, sizeof(t_paths));
	load_paths(scenedata, paths);
	data->paths = paths;
	if (verify_paths_data(paths))
		error_free(BAD_SCENE, data, scenedata);
//	print_paths(paths);
	if (load_colorschemes(paths->floor_colorscheme, data->floor)
		|| load_colorschemes(paths->ceiling_colorscheme, data->ceiling))
		error_free(BAD_RGB, data, scenedata);
	print_colorschemes(data);
	if (load_map(scenedata, data))
		error_free(INVALID_MAP, data, scenedata);
	free_data_content(data);
	free(data);
}

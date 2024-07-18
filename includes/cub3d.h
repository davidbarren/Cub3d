/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 09:11:32 by dbarrene          #+#    #+#             */
/*   Updated: 2024/07/15 12:37:02 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "parsing.h"
# include <stdio.h>
# include <math.h>
# include <string.h>



/****************************
 * *********MACROS***********
 * *************************/
# define WINDOW_HEIGHT 1200
# define WINDOW_WIDTH 2080
# define PI 3.141592653589793
# define PIXEL_SIZE 50
/****************************
 * *********TYPEDEFS*********
 * *************************/
enum e_errors
{
	OPEN_FAILURE,
	CLOSE_FAILURE,
	MALLOC_FAILURE,
	SPLIT_FAILURE,
	PERMS_FAILURE,
	NONEXISTING_FILE,
	BAD_FORMAT,
	BAD_ARGS,
	BAD_RGB,
	BAD_SCENE,
	INVALID_MAP,

};

typedef struct s_paths
{
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	char	*floor_colorscheme;
	char	*ceiling_colorscheme;
}	t_paths;

typedef struct s_file
{
	char		*filename;
	char		**scene_data;
	char		*fullscene;
	t_paths		*textures;
	int			map_index;
}	t_file;

typedef struct s_player
{
	double x_pos;
	double y_pos;
}	t_player;

typedef struct s_spritedata
{
	mlx_texture_t *north_wall_txt;
	mlx_texture_t *south_wall_txt;
	mlx_texture_t *east_wall_txt;
	mlx_texture_t *west_wall_txt;
	mlx_image_t *north_wall_img;
	mlx_image_t *south_wall_img;
	mlx_image_t *east_wall_img;
	mlx_image_t *west_wall_img;
}	t_spritedata;

typedef struct s_gamedata
{
	t_player	*playerdata;
	char		**map;
	t_paths		*paths;
	uint8_t		floor[3];
	uint8_t		ceiling[3];
	mlx_t		*window;
}	t_gamedata;

// debug and print functions
void	print_2d(char **arr);
void	print_paths(t_paths *paths);
void	print_colorschemes(t_gamedata *data);
// errors_and_freeing
void	error_exit(int status);
void	error_free(int status, t_gamedata *data, t_file *scenedata);
void	free_data_content(t_gamedata *data);
// reading scene file
void	scene_opening(t_file *filedata);
void	load_scene(t_file *filedata, int fd);
void	file_validation(t_file *filedata, int argc, char **av);
// parsing scene file
int			map_validation(char	**map);
t_gamedata *scene_parsing(t_file *scenedata);
int			verify_paths_data(t_paths *paths);
int			load_map(t_file *scenedata, t_gamedata *data);
int			is_border(char *line);
//parsing utils
int		ft_is_whitespace(char c);
int		ft_atoi_rgb(char *str);
char	*ft_strtok(char *str, char delim);
// scene_validation
int		verify_paths_data(t_paths *paths);
// gamestate
void	init_gamestate(t_gamedata *data);
#endif

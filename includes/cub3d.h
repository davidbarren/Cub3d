/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:00:28 by dbarrene          #+#    #+#             */
/*   Updated: 2024/09/01 16:19:51 by dbarrene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/includes/libft.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <math.h>
# include <string.h>

/****************************
 * *********MACROS***********
 * *************************/
# define WINDOW_HEIGHT 1200
# define WINDOW_WIDTH 2080
# define PI 3.141592653589793
# define PIXEL_SIZE 10
# define COLLISION_MARGIN 0.1f 
# define FOV 0.66 
# define NUM_RAYS WINDOW_WIDTH
# define CUBE_HEIGHT 64
# define MOVE_SPEED 0.08f
# define TURN_SPEED 0.08f
# define TURN_SPEED_MOUSE 0.02f
# define STARTING_MARG 0.5f
# define WALL_HEIGHT 1.0f
/****************************
 * *********TYPEDEFS*********
 * *************************/

enum e_errors
{
	OPEN_FAILURE = 1,
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
	EMPTY_FILE,
	BAD_MAP,
	BAD_LOADING,
	BAD_MLX_INIT,
	BAD_NEW_IMG,
	BAD_ADDING_IMG,
	BAD_KEY_LOOP,
};

enum	e_player_orientation
{
	NORTH = 1,
	EAST = 2,
	SOUTH = 3,
	WEST = 4,
};

typedef struct s_intersection
{
	float	distance;
	float	x;
	float	y;
	int		side;
	float	ray_dir_x;
	float	ray_dir_y;
	float	true_ang;
	int		direction;
}	t_intersection;

typedef struct s_raydata
{
	float	ray_dir_x;
	int		step_x;
	float	dx;
	float	ray_dir_y;
	float	dy;
	int		step_y;
	int		direction;
	int		side;
	bool	collided;
	float	camera_dist;
	float	x_dist;
	float	y_dist;
	int		map_x;
	int		map_y;

}	t_raydata;

typedef struct s_paths
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
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
	float		x_pos;
	float		y_pos;
	float		angle;
}	t_player;

typedef struct s_line_params
{
	int	dx;
	int	dy;
	int	ray_xdir;
	int	ray_ydir;
	int	x_ray;
	int	y_ray;
}	t_line_params;

typedef struct s_render_params
{
	int		wall_height;
	int		wall_top;
	int		wall_bottom;
	int		y_offset;
	int		tex_x;
	int		tex_y;
	float	wall_x;
}	t_render_params;

typedef struct s_gamedata
{
	t_player		*playerdata;
	t_intersection	intersection;
	t_line_params	line;
	t_render_params	render;
	char			**map;
	t_paths			*paths;
	uint8_t			floor[3];
	uint8_t			ceiling[3];
	mlx_image_t		player;
	mlx_image_t		*img;
	mlx_texture_t	*txtrs[4];
	mlx_t			*window;
	int				flag;
	int				pixel_size;
	size_t			height;
	size_t			width;
}	t_gamedata;

// debug and print functions
void		print_2d(char **arr);
void		print_paths(t_paths *paths);
void		print_colorschemes(t_gamedata *data);
void		print_gamedata(t_gamedata *data);
// errors_and_freeing
void		error_exit(int status);
void		error_free(int status, t_gamedata *data, t_file *scenedata);
void		free_data_content(t_gamedata *data);
// reading scene file
uint32_t	get_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
void		scene_opening(t_file *filedata);
void		load_scene(t_file *filedata, int fd);
void		file_validation(t_file *filedata, int argc, char **av);
// parsing scene file
int			map_validation(char	**map);
int			verify_paths_data(t_paths *paths);
int			load_map(t_file *scenedata, t_gamedata *data);
int			is_border(char *line);
t_gamedata	*scene_parsing(t_file *scenedata);
//parsing utils
int			ft_is_whitespace(char c);
int			ft_atoi_rgb(char *str);
char		*ft_strtok(char *str, char delim);
void		ft_skip_spaces(char **str);
// scene_validation
int			verify_paths_data(t_paths *paths);
void		verify_map(t_gamedata *data);
// gamestate
void		init_gamestate(t_gamedata *data);
void		render_walls(t_gamedata *data, mlx_texture_t	*texture);
// player_data
void		find_player_pos(t_gamedata *data, char **map);
int			is_player_dir(char c);
//casting
float		get_wall_x(t_gamedata *data);
void		draw_walls(int x, mlx_texture_t *texture, t_gamedata *data,
				t_render_params *render);
// textures
void		load_texture(t_gamedata *data);
void		delete_textures(t_gamedata *data);
// dda
void		dda_new(t_gamedata *data, float rayangle);
//movement.c
void		cub3d_keyhook(void *param);
//lines.c
void		ft_put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
#endif

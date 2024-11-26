#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <mlx.h>
# include <libft.h>
# include <get_next_line.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include "darray.h"

# define WIDTH 2000
# define HEIGHT 2000

typedef struct s_colorf
{
	float	a;
	float	r;
	float	g;
	float	b;
}	t_colorf;

typedef enum e_component_type
{
	COMP_FAIL = -1,
	COMP_LIGHT,
	COMP_CAMERA,
	COMP_AMBIENT,
	COMP_SPHERE,
	COMP_PLANE,
	COMP_CYLINDER
}	t_component_type;

typedef struct s_camera
{
	t_vec3	position; // x, y, z
	t_vec3	orientation; // x, y, z normalized
	float	fov; // [0, 180]
}	t_camera;


typedef struct s_ambient
{
	float strength; // [0.0, 1.0]
	t_color color; // A:[0, 0] R:[0, 255] G:[0, 255] B:[0, 255]
}	t_ambient;

typedef struct s_light
{
	t_vec3	position; // x, y, z
	float	brightness; // [0.0, 1.0]
	t_color color; // A:[0, 0] R:[0, 255] G:[0, 255] B:[0, 255]
}	t_light;

typedef struct sphere
{
	t_vec3	position; // x, y, z
	float	radius; // > 0
	t_color	color; // A:[0, 0] R:[0, 255] G:[0, 255] B:[0, 255]
}	t_sphere;

typedef struct s_plane
{
	t_vec3	position; // x, y, z
	t_vec3	normal; // x, y, z normalized
	t_color	color; // A:[0, 0] R:[0, 255] G:[0, 255] B:[0, 255]
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	position; // x, y, z
	t_vec3	orientation; // x, y, z normalized
	float	diameter; // > 0
	float	height; // > 0
	t_color	color; // A:[0, 0] R:[0, 255] G:[0, 255] B:[0, 255]
}	t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	char		*scene_path;
	t_darray	*scene_file;
	t_darray	*spheres;
	t_darray	*planes;
	t_darray	*cylinders;
}	t_scene;

typedef struct s_timer
{
	struct timeval	start;
	struct timeval	end;
}	t_timer;

typedef struct s_check
{
	t_bool		ambient;
	t_bool		camera;
	t_bool		light;
}	t_check;

typedef struct s_rt
{
	t_mlx	mlx;
	t_check	check;
	t_scene	scene;
	t_timer	timer;
	t_bool	key_states[MAX_KEY_COUNT];
}	t_rt;

//utils
int			count_dpointer(char **str);
void		free_dpointer(char **str);
float		ft_atof(char *str);
int			cntrl_nbr(char *str);
int			parse_color(t_color *color, char *line);
int			parse_vec3(t_vec3 *vec3, char *line);
t_colorf	color_to_colorf(t_color color);
t_color		colorf_to_color(t_colorf color);

//scene
int			read_scene(t_rt *rt);
int			parse_scene(t_rt *rt);
int			control_extension(char *path);

//component
int			parse_ambient(t_rt *rt, char *line);
int			parse_camera(t_rt *rt, char *line);
int			parse_light(t_rt *rt, char *line);

//u_component
int			parse_sphere(t_rt *rt, char *line);
int			parse_plane(t_rt *rt, char *line);
int			parse_cylinder(t_rt *rt, char *line);

//display
int			init_display(t_rt *rt);
int			terminate_display(t_mlx *mlx);

//display_inputs
int			terminate_program(t_rt *rt);
int			key_press(int keycode, t_rt *rt);
int			key_release(int keycode, t_rt *rt);

//update
int			update_frame(t_rt *rt);

//render
void		render(t_rt *rt);

//debug
void		print_debug(void *comp, t_component_type type);
void		display_debug_time(t_rt *rt);
void		debug_print_scene(t_rt *rt);

#endif
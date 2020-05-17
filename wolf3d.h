/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:06:18 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:29:33 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "./libs/libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "./libs/minilibx_macos/mlx.h"
# include "pthread.h"

typedef struct	s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct	s_img
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*adr;
	int			width;
	int			height;
	int			bitspp;
	int			size_line;
	int			endian;
}				t_img;

typedef struct	s_player
{
	double		x;
	double		y;
	int			pov;
}				t_player;

typedef struct	s_block
{
	int			x;
	int			y;
	int			id;
}				t_block;
typedef struct	s_lodev
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}				t_lodev;

typedef struct	s_map
{
	t_vector	floor;
	t_vector	camera;
	t_vector	ray_dir;
	t_vector	map;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	t_vector	step;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			x;
	int			color;

}				t_map;
typedef struct	s_key
{
	double		speed;
	double		angle;
	int			speed_flag;
	int			step_flag;
}				t_key;

typedef struct	s_menu
{
	int			x;
	int			y;
	int			xl;
	int			xr;
	int			yu;
	int			yd;
	int			p;
	int			dx;
	int			dy;
	int			flag_menu;
	int			str_col;
	int			menu_exists;
	int			speed_flag;
}				t_menu;

typedef struct	s_texture
{
	int			x;
	int			y;
	double		factor;
	t_img		img;
}				t_texture;
typedef struct	s_wolf
{
	char		*titel;
	int			xwin;
	int			ywin;
	int			xpr;
	int			ypr;
	int			width;
	int			height;
	t_img		img;
	t_block		*block;
	t_player	player_start;
	t_player	player_cond;
	t_lodev		dev;
	t_map		map;
	t_menu		menu;
	t_texture	projection;
	int			*move;
	int			t;
	int			l_color;
	int			talos;
	t_key		key;
	t_img		*textures;
}				t_wolf;
int				ft_map_validation(t_wolf *wolf);
int				ft_mapread(int *fd, t_wolf *wolf);
int				main(int argc, char **argv);
double			ft_dig_to_rad(int angle);
t_img			*ft_delimage(t_img *img);
void			ft_image_set_pixel(t_img *img, int x, int y, int color);
void			ft_new_image(t_img *img);
t_block			ft_pos(t_wolf *wolf, int x, int y);
void			ft_cast_ray(t_wolf *w);
void			ft_key(t_img *img, t_wolf *f);
void			ft_move_player(t_wolf *w, double step);
void			ft_rotate_player(t_wolf *w, int key);
int				ft_reset_key(int key, t_wolf *w);
void			ft_speed(t_wolf *w);
void			ft_menu(t_wolf *w);
void			ft_start(t_wolf *w);
void			ft_draw(t_wolf *w);
void			ft_read_textures(t_wolf *wolf);
int				ft_get_pixel(t_img *img, int x, int y);
void			ft_choose_lvl(t_wolf *w, int *fd);
void			ft_init(t_wolf *w);
void			ft_init_mlx(t_wolf *w);
void			ft_two_gc(t_wolf *w, char *argv, int *fd);
void			ft_one_gc(t_wolf *w);
void			ft_draw_floor(t_wolf *w, int y);
void			ft_init_lodev(t_wolf *w);
void			ft_calculate(t_wolf *w);
void			ft_step(t_wolf *w);
#endif

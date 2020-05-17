/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:10:05 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 20:15:04 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_exit_x(t_img *img)
{
	mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	system("./scripts/killscript");
	system("pkill afplay");
	exit(1);
	return (0);
}

static int		ft_ch_key(int key, t_wolf *f)
{
	if (key == 45)
		f->talos = (f->talos + 1) % 2;
	if (key == 53)
		ft_exit_x(&(f->img));
	if (((key == 126 || key == 13) && f->menu.flag_menu == 0)
		|| (f->move[0]))
		ft_move_player(f, 0.1f);
	if (((key == 125 || key == 1) && f->menu.flag_menu == 0)
		|| (f->move[1]))
		ft_move_player(f, -0.1f);
	if (((key == 124 || key == 2) && f->menu.flag_menu == 0)
		|| (f->move[2]))
		ft_rotate_player(f, key);
	if (((key == 123 || key == 0) && f->menu.flag_menu == 0)
		|| (f->move[3]))
		ft_rotate_player(f, key);
	else if ((key == 257 || key == 258) && f->menu.flag_menu == 0)
		ft_speed(f);
	else if ((key == 125 || key == 126) && f->menu.flag_menu != 0)
		ft_menu(f);
	else if (key == 36 && f->menu.flag_menu != 0)
		ft_draw(f);
	if (f->menu.flag_menu == 0)
		ft_cast_ray(f);
	return (0);
}

static int		ft_launch_loop_hook(t_wolf *w)
{
	ft_ch_key(-1, w);
	return (0);
}

void			ft_key(t_img *img, t_wolf *f)
{
	mlx_hook(img->win_ptr, 3, 0, ft_reset_key, f);
	mlx_hook(img->win_ptr, 2, 0, ft_ch_key, f);
	mlx_hook(img->win_ptr, 17, 0, ft_exit_x, img);
	mlx_loop_hook(img->mlx_ptr, ft_launch_loop_hook, f);
}

void			ft_choose_lvl(t_wolf *w, int *fd)
{
	system("./scripts/killscript");
	if (ft_mapread(fd, w))
		ft_return("error");
	if (w->talos == 0)
		system("./scripts/wolf_play_electro &");
	else
		system("./scripts/wolf_play_sigils &");
}

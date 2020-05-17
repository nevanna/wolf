/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:12:10 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:12:31 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_init_menu(t_wolf *w)
{
	mlx_clear_window(w->img.mlx_ptr, w->img.win_ptr);
	ft_bzero(w->img.adr, w->img.width * w->img.height * w->img.bitspp);
	w->menu.x = 0;
	w->menu.y = -1;
	w->menu.p = 25;
	w->menu.flag_menu++;
	w->menu.dx = (w->img.width / 2) * w->menu.p / 100;
	if (w->menu.dx % 2 != 0)
		w->menu.dx++;
	w->menu.xl = (w->img.width / 2) - w->menu.dx / 2;
	w->menu.xr = (w->img.width / 2) + w->menu.dx / 2;
	w->menu.dy = (w->img.height / 2) * w->menu.p / 100;
	if (w->menu.dy % 2 != 0)
		w->menu.dy++;
	w->menu.yd = (w->img.height / 2) + w->menu.dy / 2;
	w->menu.yu = (w->img.height / 2) - w->menu.dy / 2;
	w->menu.str_col = 0x003153;
	w->menu.menu_exists = 1;
}

void			ft_colorize(t_wolf *w)
{
	w->menu.y = w->menu.yu;
	if (w->menu.flag_menu % 2 != 0)
	{
		while (w->menu.y <= (w->menu.yu + 20))
		{
			w->menu.x = w->menu.xl;
			while (w->menu.x <= w->menu.xr)
				ft_image_set_pixel(&(w->img), w->menu.x++, w->menu.y, 0xffffff);
			w->menu.y++;
		}
	}
	else if (w->menu.flag_menu % 2 == 0)
	{
		w->menu.y = w->menu.yu + 30;
		while (w->menu.y <= (w->menu.yu + 20 + 30))
		{
			w->menu.x = w->menu.xl;
			while (w->menu.x <= w->menu.xr)
				ft_image_set_pixel(&(w->img), w->menu.x++, w->menu.y, 0xffffff);
			w->menu.y++;
		}
	}
}

void			ft_menu(t_wolf *w)
{
	ft_init_menu(w);
	while (++w->menu.y < w->img.height)
	{
		w->menu.x = -1;
		while (++w->menu.x < w->img.width)
		{
			if (w->menu.x >= w->menu.xl && w->menu.x <= w->menu.xr)
				ft_image_set_pixel(&(w->img), w->menu.x, w->menu.y, 0xffdead);
			else if ((w->menu.x >= 0 && w->menu.x < w->menu.xl) ||
				(w->menu.x > w->menu.xr && w->menu.x <= w->img.width))
				ft_image_set_pixel(&(w->img), w->menu.x, w->menu.y,
				ft_get_pixel(&w->textures[4], w->menu.x * 1.9, w->menu.y * 2));
			if ((w->menu.x == (w->menu.xl - 1) || w->menu.x == (w->menu.xr + 1))
			&& (w->menu.y % 3 == 0))
				ft_image_set_pixel(&(w->img), w->menu.x, w->menu.y, 990066);
		}
	}
	ft_colorize(w);
	mlx_put_image_to_window(w->img.mlx_ptr, w->img.win_ptr,
		w->img.img_ptr, 0, 0);
	mlx_string_put(w->img.mlx_ptr, w->img.win_ptr, w->menu.xl + 55,
		w->menu.yu, w->menu.str_col, "Start");
	mlx_string_put(w->img.mlx_ptr, w->img.win_ptr, w->menu.xl + 50,
		w->menu.yu + 30, w->menu.str_col, "Level 2");
	ft_key(&(w->img), w);
}

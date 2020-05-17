/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:06:55 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:26:31 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_wolf *w)
{
	int	fd;

	fd = 0;
	system("pkill afplay");
	if (w->menu.flag_menu % 2 != 0)
	{
		w->menu.flag_menu = 0;
		fd = open("map1", O_RDONLY);
		if (ft_mapread(&fd, w))
			ft_return("error");
		ft_start(w);
	}
	else if (w->menu.flag_menu % 2 == 0)
	{
		fd = open("map2", O_RDONLY);
		ft_choose_lvl(w, &fd);
		w->menu.flag_menu = 0;
		w->menu.menu_exists = 2;
		ft_cast_ray(w);
	}
}

int				ft_reset_key(int key, t_wolf *w)
{
	if (key == 126 || key == 13)
		w->move[0] = 0;
	if (key == 125 || key == 1)
		w->move[1] = 0;
	if (key == 124 || key == 2)
		w->move[2] = 0;
	if (key == 123 || key == 0)
		w->move[3] = 0;
	return (0);
}

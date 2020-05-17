/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmanfred <cmanfred@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:48:24 by cmanfred          #+#    #+#             */
/*   Updated: 2019/03/16 14:00:49 by cmanfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void		ft_launch_level(t_wolf *w)
{
	if (w->menu.menu_exists == 0)
		return ;
	if (w->menu.menu_exists == 2 || w->menu.menu_exists == 3)
	{
		system("./scripts/killscript");
		ft_return("You passed the game. CONGRATS!!!");
	}
	if (w->menu.menu_exists == 1)
	{
		w->dev.plane.x = 0;
		w->dev.plane.y = 2.0f / 3.0f;
		w->menu.speed_flag = 0;
		ft_draw(w);
	}
	w->menu.menu_exists++;
}

void		ft_move_player(t_wolf *w, double step)
{
	t_vector	p;

	w->move[(step > 0.0f ? 0 : 1)] = 1;
	w->key.step_flag++;
	if ((w->key.step_flag % 20 == 0 && w->key.speed_flag == 0) ||
		(w->key.step_flag % 10 == 0 && w->key.speed_flag != 0))
		system("afplay -t 0.2 -v 0.5 sounds/gravel.wav &");
	if (w->key.speed_flag == 0)
		w->key.speed = 0.4f;
	p = w->dev.pos;
	if (ft_pos(w, p.x + step * 2 * w->dev.dir.x, p.y).id == 0)
		w->dev.pos.x += step * w->key.speed * w->dev.dir.x;
	p = w->dev.pos;
	if (ft_pos(w, p.x, p.y + step * 2 * w->dev.dir.y).id == 0)
		w->dev.pos.y += step * w->key.speed * w->dev.dir.y;
	if ((ft_pos(w, p.x + step * 8 * w->dev.dir.x, w->dev.pos.y).id == 1488)
		|| (ft_pos(w, w->dev.pos.x, p.y + step * 8 * w->dev.dir.y).id == 1488))
		ft_launch_level(w);
}

void		ft_speed(t_wolf *w)
{
	if (w->key.speed_flag == 0)
	{
		w->key.speed_flag = 2;
		w->key.speed = 0.8f;
	}
	else
	{
		w->key.speed_flag = 0;
		w->key.speed = 0.4f;
	}
}

void		ft_rotate(t_vector *v, double angle)
{
	double	tmp;
	double	co;
	double	si;

	tmp = v->x;
	co = cos(angle);
	si = sin(angle);
	v->x = v->x * co - v->y * si;
	v->y = v->y * co + tmp * si;
}

void		ft_rotate_player(t_wolf *w, int key)
{
	double	angle;

	angle = 0;
	if (key == 124 || key == 2)
		w->move[2] = 1;
	else if (key == 123 || key == 0)
		w->move[3] = 1;
	w->key.angle = 0.08f;
	w->key.step_flag++;
	if ((w->key.step_flag % 30 == 0 && w->key.speed_flag == 0) ||
		(w->key.step_flag % 15 == 0 && w->key.speed_flag != 0))
		system("afplay -t 0.2 -v 0.4 sounds/gravel.wav &");
	if (w->move[2] == 1)
		angle = w->key.angle;
	else if (w->move[3] == 1)
		angle = -(w->key.angle);
	if (w->move[1] == 1 && w->move[0] == 0)
		angle *= -1;
	ft_rotate(&(w->dev.dir), angle);
	ft_rotate(&(w->dev.plane), angle);
}

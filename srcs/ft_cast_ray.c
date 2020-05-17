/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:25:36 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:33:01 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_step(t_wolf *w)
{
	if (w->map.ray_dir.x < 0)
	{
		w->map.step.x = -1;
		w->map.side_dist.x = (w->dev.pos.x -
			w->map.map.x) * w->map.delta_dist.x;
	}
	else
	{
		w->map.step.x = 1;
		w->map.side_dist.x = (w->map.map.x + 1 -
			w->dev.pos.x) * w->map.delta_dist.x;
	}
	if (w->map.ray_dir.y < 0)
	{
		w->map.step.y = -1;
		w->map.side_dist.y = (w->dev.pos.y -
			w->map.map.y) * w->map.delta_dist.y;
	}
	else
	{
		w->map.step.y = 1;
		w->map.side_dist.y = (w->map.map.y + 1 -
			w->dev.pos.y) * w->map.delta_dist.y;
	}
}

void		ft_draw_floor(t_wolf *w, int y)
{
	double	curr;
	double	weight;
	int		fx;
	int		fy;

	while (y <= w->img.height)
	{
		curr = w->img.height / (2.0f * y - w->img.height);
		weight = curr / w->map.perp_wall_dist;
		fx = (int)((weight * w->map.floor.x + (1.0f - weight) * w->dev.pos.x)
			* w->textures[6].width) % w->textures[6].width;
		fy = (int)((weight * w->map.floor.y + (1.0f - weight) * w->dev.pos.y)
			* w->textures[6].height) % w->textures[6].height;
		ft_image_set_pixel(&w->img, w->map.x, y,
			ft_get_pixel(&w->textures[6], fx, fy));
		fx = (int)((weight * w->map.floor.x + (1.0f - weight) * w->dev.pos.x)
			* w->textures[1].width) % w->textures[1].width;
		fy = (int)((weight * w->map.floor.y + (1.0f - weight) * w->dev.pos.y)
			* w->textures[1].height) % w->textures[1].height;
		ft_image_set_pixel(&w->img, w->map.x, w->img.height - y,
			ft_get_pixel(&w->textures[1], fx, fy));
		y++;
	}
}

void		ft_ver_line(t_wolf *w)
{
	int		y;

	y = w->map.draw_start - 1;
	ft_draw_floor(w, w->map.draw_end);
	while (++y < w->map.draw_end + 1)
	{
		w->projection.y = ((y - w->img.height / 2 + w->map.line_height / 2)
			* w->projection.img.height) / w->map.line_height;
		ft_image_set_pixel(&(w->img), w->map.x, y,
			ft_get_pixel(&w->projection.img, w->projection.x, w->projection.y));
	}
}

static void	ft_floor_init(t_wolf *w)
{
	w->map.floor.x = (double)w->map.map.x + (w->map.side ?
		w->projection.factor : 0) +
		(!w->map.side && w->map.ray_dir.x < 0 ? 1.0f : 0);
	w->map.floor.y = (double)w->map.map.y + (w->map.side ?
		0 : w->projection.factor) +
		(w->map.side && w->map.ray_dir.y < 0 ? 1.0f : 0);
}

void		ft_calculate(t_wolf *w)
{
	if (w->map.side == 0)
		w->map.perp_wall_dist = (w->map.map.x - w->dev.pos.x +
			(1 - w->map.step.x)
				/ 2) / w->map.ray_dir.x;
	else
		w->map.perp_wall_dist = (w->map.map.y - w->dev.pos.y +
			(1 - w->map.step.y)
				/ 2) / w->map.ray_dir.y;
	w->map.line_height = (int)(w->img.height / w->map.perp_wall_dist);
	w->map.draw_start = -w->map.line_height / 2 + w->img.height / 2;
	if (w->map.draw_start < 0)
		w->map.draw_start = 0;
	w->map.draw_end = w->map.line_height / 2 + w->img.height / 2;
	if (w->map.draw_end >= w->img.height)
		w->map.draw_end = w->img.height - 1;
	w->projection.factor = (w->map.side ? w->dev.pos.x + w->map.perp_wall_dist *
		w->map.ray_dir.x : w->dev.pos.y + w->map.perp_wall_dist *
			w->map.ray_dir.y);
	w->projection.factor -= floor(w->projection.factor);
	w->projection.x = (int)(w->projection.factor * w->projection.img.width);
	ft_floor_init(w);
	ft_ver_line(w);
}

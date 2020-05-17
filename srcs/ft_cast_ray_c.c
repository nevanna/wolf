/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_ray_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:37:56 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:38:10 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_which_texture(t_wolf *w)
{
	if ((ft_pos(w, w->map.map.x, w->map.map.y)).id == 1488)
		w->projection.img = w->textures[5];
	else if (w->map.side == 0)
	{
		if (w->map.step.x > 0)
			w->projection.img = w->textures[0];
		else
			w->projection.img = w->textures[1];
	}
	else
	{
		if (w->map.step.y > 0)
			w->projection.img = w->textures[2];
		else
			w->projection.img = w->textures[3];
	}
}

void		ft_dda(t_wolf *w)
{
	while (w->map.hit == 0)
	{
		if (w->map.side_dist.x < w->map.side_dist.y)
		{
			w->map.side_dist.x += w->map.delta_dist.x;
			w->map.map.x += w->map.step.x;
			w->map.side = 0;
		}
		else
		{
			w->map.side_dist.y += w->map.delta_dist.y;
			w->map.map.y += w->map.step.y;
			w->map.side = 1;
		}
		if ((ft_pos(w, w->map.map.x, w->map.map.y)).id > 0)
			w->map.hit = 1;
	}
	ft_which_texture(w);
	ft_calculate(w);
}

void		ft_cast_ray(t_wolf *w)
{
	ft_bzero(w->img.adr, w->img.width * w->img.height * w->img.bitspp);
	mlx_clear_window(w->img.mlx_ptr, w->img.win_ptr);
	w->map.x = 0;
	w->projection.img = w->textures[0];
	while (w->map.x < w->img.width)
	{
		w->map.camera.x = 2 * w->map.x / (double)(w->img.width) - 1;
		w->map.ray_dir.x = w->dev.dir.x + w->dev.plane.x * w->map.camera.x;
		w->map.ray_dir.y = w->dev.dir.y + w->dev.plane.y * w->map.camera.x;
		w->map.map.x = (int)(w->dev.pos.x);
		w->map.map.y = (int)(w->dev.pos.y);
		w->map.delta_dist.x = fabs(1 / w->map.ray_dir.x);
		w->map.delta_dist.y = fabs(1 / w->map.ray_dir.y);
		w->map.hit = 0;
		ft_step(w);
		ft_dda(w);
		w->map.x++;
	}
	mlx_put_image_to_window(w->img.mlx_ptr, w->img.win_ptr,
		w->img.img_ptr, 0, 0);
}

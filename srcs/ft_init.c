/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:09:42 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:09:49 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_init_mlx(t_wolf *w)
{
	if ((w->img.mlx_ptr = mlx_init()) == NULL)
		ft_return("error: mlx");
	if ((w->img.win_ptr = mlx_new_window(w->img.mlx_ptr, w->img.width,
		w->img.height, w->titel)) == NULL)
		ft_return("error: mlx");
	if ((w->img.img_ptr = mlx_new_image(w->img.mlx_ptr, w->img.width,
		w->img.height)) == NULL)
		ft_return("error:img_ptr");
	w->img.adr = mlx_get_data_addr(w->img.img_ptr, &(w->img.bitspp),
		&(w->img.size_line), &(w->img.endian));
	w->img.bitspp /= 8;
	w->textures = (t_img *)malloc(sizeof(t_img) * 20);
	ft_read_textures(w);
}

void		ft_init_lodev(t_wolf *w)
{
	w->dev.plane.x = 0;
	w->dev.plane.y = 2.0f / 3.0f;
	w->img.size_line = 0;
	w->key.step_flag = 0;
}

void		ft_init(t_wolf *w)
{
	w->menu.menu_exists = 0;
	w->titel = "WOLF 3D";
	w->img.height = 720;
	w->img.width = 1280;
	w->map.color = 0xFF;
	w->talos = 0;
	w->move = ft_memalloc(sizeof(int) * 4);
	ft_init_lodev(w);
}

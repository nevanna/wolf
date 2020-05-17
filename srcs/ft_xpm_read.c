/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpm_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:38:31 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 19:38:52 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_img	ft_get_xpm(char *file, t_wolf *w)
{
	t_img	img;

	if ((img.img_ptr = mlx_xpm_file_to_image(w->img.mlx_ptr,
		file, &img.width, &img.height)) == NULL)
		ft_return("can't read textures");
	img.adr = mlx_get_data_addr(img.img_ptr, &img.bitspp,
		&img.size_line, &img.endian);
	img.bitspp /= 8;
	img.width = img.size_line / img.bitspp;
	img.height = img.width;
	return (img);
}

void			ft_read_textures(t_wolf *wolf)
{
	wolf->textures[0] = ft_get_xpm("textures/brick.xpm", wolf);
	wolf->textures[1] = ft_get_xpm("textures/metal.xpm", wolf);
	wolf->textures[2] = ft_get_xpm("textures/stone.xpm", wolf);
	wolf->textures[3] = ft_get_xpm("textures/wood.xpm", wolf);
	wolf->textures[4] = ft_get_xpm("textures/maze.xpm", wolf);
	wolf->textures[5] = ft_get_xpm("textures/g.xpm", wolf);
	wolf->textures[6] = ft_get_xpm("textures/gravel.xpm", wolf);
	wolf->textures[7] = ft_get_xpm("textures/finish.xpm", wolf);
}

double			ft_dig_to_rad(int angle)
{
	double		new_angl;
	double		pi;

	pi = 3.1415926535;
	new_angl = (((double)angle) * pi) / 180.0f;
	return (new_angl);
}

t_block			ft_pos(t_wolf *wolf, int x, int y)
{
	return (wolf->block[x + y * wolf->width]);
}

void			ft_start(t_wolf *w)
{
	system("./scripts/killscript");
	if (w->talos == 0)
		system("./scripts/wolf_play_intro &");
	else
		system("./scripts/wolf_play_sigils &");
	ft_cast_ray(w);
	ft_key(&(w->img), w);
}

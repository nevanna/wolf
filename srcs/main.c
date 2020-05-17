/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:08:48 by htillman          #+#    #+#             */
/*   Updated: 2019/03/15 20:00:00 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_usage(void)
{
	ft_return("Usage: ./wolf3d map");
}

static void	ft_valid_arg(int argc, char **argv)
{
	if (argc > 2)
		ft_usage();
	argv = (char **)(void **)argv;
}

void		ft_two_gc(t_wolf *w, char *argv, int *fd)
{
	(*fd) = open(argv, O_RDONLY);
	ft_init(w);
	if (ft_mapread(fd, w))
		ft_return("error");
	ft_init_mlx(w);
	ft_start(w);
}

void		ft_one_gc(t_wolf *w)
{
	ft_init(w);
	ft_init_mlx(w);
	ft_menu(w);
}

int			main(int argc, char **argv)
{
	t_wolf	wolf;
	int		fd;

	fd = 0;
	wolf.menu.flag_menu = 0;
	system("./scripts/wolf_play_guitar &");
	ft_valid_arg(argc, argv);
	if (argc == 1)
		ft_one_gc(&wolf);
	else if (argc == 2)
		ft_two_gc(&wolf, argv[1], &fd);
	mlx_loop(wolf.img.mlx_ptr);
	exit(1);
	return (0);
}

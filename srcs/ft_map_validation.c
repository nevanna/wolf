/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 17:30:52 by cmanfred          #+#    #+#             */
/*   Updated: 2019/03/15 17:33:37 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_init_player(t_wolf *w)
{
	t_block	*b;
	int		i;

	b = w->block;
	i = 0;
	while (b[i].id != 0)
		i++;
	w->dev.pos.x = i % w->width + 0.5f;
	w->dev.pos.y = i / w->width + 0.5f;
	w->dev.dir.x = 1.0f;
	w->dev.dir.y = 0.0f;
}

static int	ft_reason(int reason)
{
	if (reason == 1)
		ft_putendl("There are holes in map perimiter");
	else if (reason == 2)
		ft_putendl("There is no place for spawn in the map");
	return (reason);
}

int			ft_map_validation(t_wolf *wolf)
{
	t_block	*b;
	int		i;
	int		flag;

	b = wolf->block;
	i = -1;
	while (++i < wolf->width)
		if (b[i].id == 0 || b[i + wolf->width * (wolf->height - 1)].id == 0)
			return (ft_reason(1));
	i = -1;
	while (++i < wolf->height)
		if (b[i * wolf->width].id == 0 ||
				b[i * wolf->width + wolf->width - 1].id == 0)
			return (ft_reason(1));
	i = -1;
	flag = 0;
	while (++i < wolf->width * wolf->height)
		if (b[i].id == 0)
			flag++;
	if (!flag)
		return (ft_reason(2));
	ft_init_player(wolf);
	return (0);
}

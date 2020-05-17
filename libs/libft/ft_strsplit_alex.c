/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_alex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htillman <htillman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:25:11 by htillman          #+#    #+#             */
/*   Updated: 2019/02/19 18:26:37 by htillman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				ft_prov(char **psp, size_t index, char *pzam)
{
	if (pzam == NULL)
	{
		while (index > 0)
		{
			free(psp[index]);
			index--;
		}
		free(psp[0]);
		free(psp);
		return (0);
	}
	else
		return (1);
}

static size_t			ft_quan(char const *s, char c)
{
	int					i;
	size_t				sc;
	int					l;

	i = 0;
	sc = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			l = i;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
			sc++;
			i--;
		}
		i++;
	}
	return (sc);
}

static char				**ft_nspl(char **sp, char const *s, char c)
{
	int					ni;
	size_t				nsc;
	int					nl;
	char				*zam;

	ni = 0;
	nsc = 0;
	while (s[ni] != '\0')
	{
		if (s[ni] != c)
		{
			nl = ni;
			while (s[ni] != c && s[ni] != '\0')
				ni++;
			zam = ft_strsub(s, nl, ni - nl);
			if (ft_prov(sp, nsc, zam) == 0)
				return (NULL);
			sp[nsc] = zam;
			nsc++;
			ni--;
		}
		ni++;
	}
	sp[nsc] = NULL;
	return (sp);
}

char					**ft_strsplit_alex(char const *s, char c)
{
	char				**newspl;

	if (s == NULL)
		return (NULL);
	newspl = (char **)malloc(ft_quan(s, c) * sizeof(char *) + 1);
	if (newspl == NULL)
		return (NULL);
	return (ft_nspl(newspl, s, c));
}

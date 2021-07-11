/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:44:34 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/31 20:44:53 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

void			map_elem_pars(t_all *all, char m, int x, int y)
{
	if (m == '2')
		all->sprcount++;
	else if (ft_strchr("NEWS", m) && all->plr.dir == 99)
	{
		if (m == 'N')
			all->plr.dir = NO;
		else if (m == 'S')
			all->plr.dir = SO;
		else if (m == 'W')
			all->plr.dir = WE;
		else if (m == 'E')
			all->plr.dir = EA;
		all->plr.x = x + 0.5;
		all->plr.y = y + 0.5;
	}
	else
		errormsg(12, "Only one Player allowed!");
}

void			map_check_elems(t_all *all, int i, int j)
{
	char		**m;

	m = all->map.map;
	if (m[j][i] == '1')
		return ;
	if (ft_strchr("02NEWS", m[j][i]))
	{
		if (m[j][i] != '0')
			map_elem_pars(all, m[j][i], i, j);
		map_elem_check(m[j][i + 1]);
		map_elem_check(m[j][i - 1]);
		map_elem_check(m[j + 1][i + 1]);
		map_elem_check(m[j + 1][i - 1]);
		map_elem_check(m[j - 1][i + 1]);
		map_elem_check(m[j - 1][i - 1]);
		map_elem_check(m[j + 1][i]);
		map_elem_check(m[j - 1][i]);
	}
	else if (m[j][i] != ' ' && m[j][i] != '1')
		errormsg(11, "Map error!");
}

void			map_check(t_all *all, int j)
{
	int		i;
	char	**m;

	m = all->map.map;
	i = 0;
	while (m[j][i] != '\0')
		m[j][i] == ' ' || m[j][i] == '1' ? i++ : errormsg(11, "Map error!");
	while (--j > 0)
	{
		i = 0;
		while (m[j][i] == ' ')
			i++;
		while (m[j][i] != '\0')
		{
			map_check_elems(all, i, j);
			i++;
			all->map.wide += all->map.wide < i ? 1 : 0;
		}
	}
	i = 0;
	while (m[j][i] != '\0')
		m[j][i] == ' ' || m[j][i] == '1' ? i++ : errormsg(11, "Map error!");
	if (all->plr.dir == 99)
		errormsg(8, "You forgot to specify the player!");
}

void			map_make(t_all *all, t_list **gnl, int size)
{
	int		i;
	t_list	*tmp;

	i = 0;
	if (!(all->map.map = ft_calloc(size + 1, sizeof(char *))))
		errormsg(14, "Map allocation memory failed");
	if (!all->map.map)
		return ;
	tmp = *gnl;
	while (i < size && tmp != NULL)
	{
		all->map.map[i++] = tmp->content;
		tmp = tmp->next;
	}
	map_check(all, size - 1);
}

void			map_continuity(t_all *all, t_list *gnl)
{
	t_list	*tmp;
	t_list	*last;
	int		i;

	i = 1;
	while (gnl->content && !ft_strchr(gnl->content, '1'))
		gnl->next == NULL || ((char *)gnl->content)[0] != '\0' ?
			errormsg(11, "Map error!") : (gnl = gnl->next);
	tmp = gnl;
	while (tmp->next != NULL)
	{
		last = tmp;
		tmp = tmp->next;
		i++;
		while (tmp->next != NULL && ((char *)tmp->content)[0] == '\0')
		{
			tmp = tmp->next;
			if (((char *)tmp->content)[0] != '\0')
				errormsg(11, "Map error!");
		}
	}
	i -= (!checkgnl(tmp->content)) ? 1 : 0;
	all->map.height = i;
	map_make(all, &gnl, i);
}

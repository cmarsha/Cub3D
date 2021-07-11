/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_sprites.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:47:05 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/15 22:47:09 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

void			spr_angles_quadrants(t_all *all, int i)
{
	float		dx;
	float		dy;
	float		a;

	dx = all->spr[i].fx - all->plr.x;
	dy = all->spr[i].fy - all->plr.y;
	if (dx < 0)
		a = dy >= 0 ? acos(fabs(dy) / all->spr[i].d) + M_PI_2 :
		3 * M_PI_2 - (acos(fabs(dy) / all->spr[i].d));
	else if (dx >= 0)
		a = dy >= 0 ? asin(fabs(dy) / all->spr[i].d) :
		2 * M_PI - (asin(fabs(dy) / all->spr[i].d));
	if (all->plr.dir < M_PI_2 && a > 3 * M_PI_2)
		all->spr[i].a = a - 2 * M_PI - all->plr.dir;
	else if (all->plr.dir > 3 * M_PI_2 && a < M_PI_2)
		all->spr[i].a = 2 * M_PI - all->plr.dir + a;
	else
		all->spr[i].a = a - all->plr.dir;
}

void			spr_params_counting(t_all *all, int i)
{
	t_spr		*s;

	s = all->spr;
	if (fabsf(s[i].a) < M_PI_6)
		s[i].d *= 1 - (1 - (cosf(s[i].a))) / 2;
	else
		s[i].d *= 1 - (1 - (cosf(M_PI_6))) / 2;
	s[i].h = 0.97 * all->par.ry / s[i].d;
	s[i].sty = all->win[s[i].n].y / (float)s[i].h;
	s[i].stx = s[i].sty / all->par.ratio;
	s[i].cx = (s[i].a / ((M_PI / 3) / all->par.rx)) + all->par.rx / 2;
	s[i].sx = s[i].cx - s[i].h * all->par.ratio / 2;
	s[i].ex = s[i].cx + s[i].h * all->par.ratio / 2;
	s[i].alwd = s[i].ex < 0 || s[i].sx > all->par.rx ? 0 : 1;
	all->map.map[s[i].y][s[i].x] = s[i].alwd == 1 &&
		fabsf(s[i].a) < M_PI_6 ? '2' : '5';
}

void			spr_get_allowed(t_all *all)
{
	int			i;

	i = 0;
	while (i < all->sprcount)
	{
		if (all->spr[i].d < 0.2)
		{
			all->spr[i].alwd = 0;
			i++;
			break ;
		}
		all->spr[i].d < 15.9 ? spr_angles_quadrants(all, i) : 0;
		if (all->spr[i].d < 15.9 && fabsf(all->spr[i].a) < M_PI_2)
			spr_params_counting(all, i);
		else
		{
			all->spr[i].alwd = 0;
			all->map.map[all->spr[i].y][all->spr[i].x] = '5';
		}
		i++;
	}
}

void			spr_sorting(t_all *all)
{
	t_spr		temp;
	int			i;
	int			k;

	i = all->sprcount;
	while (i > 0 && i--)
		all->spr[i].d = sqrtl(powl(all->plr.x - all->spr[i].fx, 2) +
		powl(all->plr.y - all->spr[i].fy, 2));
	spr_get_allowed(all);
	while (i++ < all->sprcount - 1)
	{
		k = i;
		while (k > 0 && all->spr[k - 1].d < all->spr[k].d)
		{
			temp = all->spr[k - 1];
			all->spr[k - 1] = all->spr[k];
			all->spr[k--] = temp;
		}
	}
}

void			spr_allocation(t_all *all)
{
	int		x;
	int		y;
	int		n;

	y = -1;
	n = 0;
	if (!(all->spr = ft_calloc(all->sprcount + 1, sizeof(t_spr))))
		errormsg(14, "Sprites allocation memory failed");
	while (all->map.map[++y] != 0)
	{
		x = -1;
		while (all->map.map[y][++x])
		{
			if (ft_strchr("23456789", all->map.map[y][x]))
			{
				all->spr[n].n = all->map.map[y][x] - 48 + 3;
				all->spr[n].x = x;
				all->spr[n].y = y;
				all->spr[n].fx = all->spr[n].x + 0.5;
				all->spr[n].fy = all->spr[n].y + 0.5;
				all->spr[n].d = 0;
				n++;
			}
		}
	}
}

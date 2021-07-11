/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycaster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:39:19 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/15 22:39:21 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw_spr_tex_x(t_all *all, int i, int x)
{
	while (x < all->par.rx && x < all->spr[i].ex)
	{
		if (all->par.perp[x] + 0.20 < all->spr[i].d)
		{
			all->spr[i].px += all->spr[i].stx;
			x++;
			continue;
		}
		all->spr[i].top = all->spr[i].stop;
		draw_tex_y(all, &all->spr[i], x, 5);
		all->spr[i].px += all->spr[i].stx;
		x++;
	}
}

void			draw_spr(t_all *all)
{
	int			i;
	int			x;

	i = 0;
	while (i < all->sprcount)
	{
		if (all->spr[i].alwd == 1)
		{
			all->spr[i].px = 0;
			x = all->spr[i].sx;
			while (x < 0)
			{
				all->spr[i].px += all->spr[i].stx;
				x++;
			}
			draw_calc_top_btm(all, &all->spr[i]);
			draw_spr_tex_x(all, i, x);
		}
		i++;
	}
}

void			draw_wall_counting_x(t_all *all, t_plr *ray, t_spr *w, int x)
{
	ray->x = all->plr.x;
	ray->y = all->plr.y;
	draw_wall_cast_rays(all, ray, w, x);
	all->par.perp[x] = w->d * (cosf(ray->start - all->plr.dir));
	ray->start += ray->step;
	w->h = all->par.rx / all->par.perp[x];
	ray->y -= (int)ray->y;
	ray->x -= (int)ray->x;
	if (all->par.wt == 'x')
		all->par.wn = ray->start > M_PI_2 && ray->start < (3 * M_PI_2) ? 1 : 3;
	else if (all->par.wt == 'y')
		all->par.wn = (ray->start > 0 && ray->start < M_PI) ||
			ray->start > 2 * M_PI ? 4 : 2;
}

void			draw_walls(t_all *all)
{
	t_spr		w;
	t_plr		ray;
	int			x;
	int			clng;

	x = 0;
	clng = 0;
	ray = all->plr;
	ray.start = ray.dir - M_PI / 6;
	ray.end = ray.dir + M_PI / 6;
	while (x < all->par.rx)
	{
		draw_wall_counting_x(all, &ray, &w, x);
		w.px = all->par.wt == 'x' ? ray.y * all->win[all->par.wn].x :
			ray.x * all->win[all->par.wn].x;
		w.sty = all->win[all->par.wn].y / (float)w.h;
		draw_calc_top_btm(all, &w);
		clng = 0;
		while (clng < w.top)
			my_mlx_pixel_put(&all->win[0], x, clng++, all->txs.c);
		draw_tex_y(all, &w, x, all->par.wn);
		while (w.top < all->par.ry)
			my_mlx_pixel_put(&all->win[0], x, w.top++, all->txs.f);
		x++;
	}
}

void			raycaster(t_all *all)
{
	spr_sorting(all);
	draw_walls(all);
	draw_spr(all);
}

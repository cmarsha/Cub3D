/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_raycaster2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:36:22 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/21 13:36:26 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned	my_mlx_pixel_out(t_win *win, int x, int y)
{
	char		*dst;
	unsigned	color;

	dst = win->addr + (y * win->ll + x * (win->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void		draw_tex_y(t_all *all, t_spr *w, int x, int texn)
{
	int		wpc;

	w->py = 0;
	while (w->top < w->btm)
	{
		if (w->top >= 0 && w->top < all->par.ry && w->py < all->win[texn].y)
		{
			wpc = my_mlx_pixel_out(&all->win[texn], w->px, w->py);
			if (wpc != 0)
				my_mlx_pixel_put(&all->win[0], x, w->top, wpc);
		}
		w->py += w->sty;
		w->top++;
	}
}

void		draw_calc_top_btm(t_all *all, t_spr *w)
{
	w->btm = all->par.horizont + w->h / 2;
	w->top = w->btm - w->h;
	w->stop = w->top;
}

int			draw_wall_raycasting(t_all *all, t_plr *ray, t_raycast *r)
{
	int		n;

	n = 0;
	while (all->map.map[(int)(ray->y)][(int)(ray->x)] != '1' && n < 250)
	{
		ray->x += r->co;
		ray->y += r->si;
		n++;
	}
	return (n);
}

void		draw_wall_cast_rays(t_all *all, t_plr *ray, t_spr *w, int x)
{
	int			i;
	int			n;
	t_raycast	r;

	i = 0;
	r.co = cosf(ray->start) * RAY_STEP;
	r.si = sinf(ray->start) * RAY_STEP;
	while (all->map.map[(int)(ray->y)][(int)(ray->x)] != '1' && i < 9)
	{
		n = 0;
		n = draw_wall_raycasting(all, ray, &r);
		r.co *= 2;
		r.si *= 2;
		i++;
	}
	ray->y -= r.si;
	all->par.wt = all->map.map[(int)ray->y][(int)ray->x] == '1' ? 'x' : 'y';
	w->d = n > 240 && i >= 8 ? 310 : sqrtf(powf(all->plr.x - ray->x, 2) +
		powf(all->plr.y - ray->y + r.si, 2));
}

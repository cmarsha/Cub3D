/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_raycaster2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:50:20 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/21 17:50:22 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

unsigned		my_mlx_pixel(t_win *win, int x, int y, t_color *col)
{
	unsigned char	tmp[4];
	unsigned		color;

	color = my_mlx_pixel_out(win, x, y);
	if (color != 0)
	{
		tmp[3] = 0;
		tmp[2] = my_rgb_manipulation(color >> 16, col->rnum, col->rden);
		tmp[1] = my_rgb_manipulation(color >> 8, col->gnum, col->gden);
		tmp[0] = my_rgb_manipulation(color, col->bnum, col->bden);
		color = *(unsigned int*)tmp;
	}
	return (color);
}

void			draw_tex_y(t_all *all, t_spr *w, int x, int texn)
{
	int		wpc;
	t_color col;

	draw_color_nums(&col, 1);
	texn == 5 && w->d > 1 && w->d <= 15.9 ? draw_shadow(&col, w->d) : 0;
	texn == 5 && w->d > 15.9 ? draw_black(all, w, &x) : 0;
	texn != 5 && all->par.perp[x] > 1 && all->par.perp[x] <= 15.9 ?
		draw_shadow(&col, all->par.perp[x]) : 0;
	texn != 5 && all->par.perp[x] > 15.9 ? draw_black(all, w, &x) : 0;
	if (x == 99999)
		return ;
	w->py = 0;
	while (w->top < w->btm)
	{
		if (w->top >= 0 && w->top < all->par.ry && w->py < all->win[texn].y)
		{
			wpc = my_mlx_pixel(&all->win[texn], w->px, w->py, &col);
			if (wpc != 0)
				my_mlx_pixel_put(&all->win[0], x, w->top, wpc);
		}
		w->py += w->sty;
		w->top++;
	}
}

void			draw_calc_top_btm(t_all *all, t_spr *w)
{
	int		k;

	k = 8;
	if (all->btn.d == 2)
		k = 4;
	if (all->btn.j == 8 || all->btn.j == 1)
		k = 10;
	else if (all->btn.j == 7 || all->btn.j == 2)
		k = 12;
	else if (all->btn.j == 6 || all->btn.j == 3)
		k = 14;
	else if (all->btn.j == 5 || all->btn.j == 4)
		k = 15;
	w->btm = all->par.horizont + k * w->h / 16;
	w->top = w->btm - w->h;
	w->stop = w->top;
}

int				draw_wall_raycasting(t_all *all, t_plr *ray, t_raycast *r)
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

void			draw_wall_cast_rays(t_all *all, t_plr *ray, t_spr *w, int x)
{
	int			i;
	int			n;
	t_raycast	r;

	i = 0;
	r.co = cosf(ray->start) * RAY_STEP;
	r.si = sinf(ray->start) * RAY_STEP;
	while (all->map.map[(int)(ray->y)][(int)(ray->x)] != '1' && i < 7)
	{
		n = 0;
		n = draw_wall_raycasting(all, ray, &r);
		r.co *= 2;
		r.si *= 2;
		i++;
	}
	ray->y -= r.si;
	all->par.wt = all->map.map[(int)ray->y][(int)ray->x] == '1' ? 'x' : 'y';
	w->d = n > 200 && i >= 7 ? 16 : sqrtf(powf(all->plr.x - ray->x, 2) +
		powf(all->plr.y - ray->y + r.si, 2));
}

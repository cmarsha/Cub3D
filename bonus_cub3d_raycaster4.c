/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_raycaster4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:57:18 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/24 22:57:20 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

void			draw_black(t_all *all, t_spr *w, int *x)
{
	while (w->top < w->btm)
	{
		if (w->top >= 0 && w->top < all->par.ry)
			my_mlx_pixel_put(&all->win[0], *x, w->top, 0x010101);
		w->top++;
	}
	*x = 99999;
}

void			draw_map_rays(t_all *all, t_plr *r)
{
	float	co;
	float	si;

	co = cos(r->start) * RAY_MAP_STEP;
	si = sin(r->start) * RAY_MAP_STEP;
	while (all->map.map[(int)(r->y / SCALE)][(int)(r->x / SCALE)] != '1')
	{
		r->x += co;
		r->y += si;
		if (all->map.map[(int)(r->y / SCALE)][(int)(r->x / SCALE)] == '2')
			my_mlx_pixel_put(&all->win[0], r->x, r->y, MAP_ASPR_COLOR);
		else if (all->map.map[(int)(r->y / SCALE)][(int)(r->x / SCALE)] == '5')
			my_mlx_pixel_put(&all->win[0], r->x, r->y, MAP_SPR_COLOR);
		else
			my_mlx_pixel_put(&all->win[0], r->x, r->y, RAY_MAP_COLOR);
	}
}

void			draw_map_backgroung(t_all *all)
{
	int		x;
	int		y;
	int		color;
	t_color	col;

	x = 0;
	col.rnum = 2;
	col.rden = 3;
	col.gnum = 2;
	col.gden = 3;
	col.bnum = 2;
	col.bden = 3;
	while (x < all->map.wide * SCALE)
	{
		y = 0;
		while (y < all->map.height * SCALE)
		{
			color = my_mlx_pixel(&all->win[0], x, y, &col);
			my_mlx_pixel_put(&all->win[0], x, y++, color);
		}
		x++;
	}
}

void			draw_map(t_all *all)
{
	int		x;
	int		y;
	t_plr	ray;

	ray = all->plr;
	ray.start = ray.dir - M_PI;
	ray.end = ray.dir + M_PI;
	draw_map_backgroung(all);
	while (ray.start <= ray.end)
	{
		ray.x = all->plr.x * SCALE;
		ray.y = all->plr.y * SCALE;
		draw_map_rays(all, &ray);
		ray.start += (2 * M_PI) / 380;
	}
	if (ray.xcd != 0 && ray.yad != 0)
	{
		x = ray.xcd * SCALE;
		while (x++ < ray.xab * SCALE)
		{
			y = ray.yad * SCALE;
			while (y < ray.ybc * SCALE)
				my_mlx_pixel_put(&all->win[0], x, y++, 0xFFFFFF);
		}
	}
}

void			engine_pause(t_all *all)
{
	int		x;
	int		y;

	if (all->btn.pause == 3)
	{
		x = 0;
		while (x < all->par.rx)
		{
			y = 0 + (x % 2);
			while (y++ < all->par.ry - 1)
				my_mlx_pixel_put(&all->win[0], x, y++, 0x666666);
			x += 1;
		}
		all->mous.fckn = 0;
		all->btn.pause = 2;
		mlx_mouse_show();
		mlx_put_image_to_window(all->mlx, all->wind, all->win[0].img, 0, 0);
	}
	all->btn.pause == 2 ? mlx_mouse_show() : 0;
	if (all->btn.pause == 1)
	{
		ft_bzero(&all->btn, 48);
		raycaster(all);
		mlx_put_image_to_window(all->mlx, all->wind, all->win[0].img, 0, 0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_movements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:39:25 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/17 21:39:43 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

int				mov_key_press(int kc, t_all *all)
{
	kc == 53 ? exit(0) : 0;
	kc == 2 ? all->btn.mr = 1 : 0;
	kc == 0 ? all->btn.ml = 1 : 0;
	kc == 13 ? all->btn.mf = 1 : 0;
	kc == 1 ? all->btn.mb = 1 : 0;
	kc == 123 ? all->btn.rl = 1 : 0;
	kc == 124 ? all->btn.rr = 1 : 0;
	kc == 126 ? all->btn.ru = 1 : 0;
	kc == 125 ? all->btn.rd = 1 : 0;
	kc == 256 ? all->btn.walk = 2 : 0;
	if (kc == 49 && all->btn.j <= 0)
	{
		all->btn.j = 8;
		all->btn.d = 0;
	}
	if (kc == 257)
	{
		all->btn.d = all->btn.d == 2 ? 1 : 2;
		all->btn.smth = 1;
	}
	all->btn.walk2 = all->btn.d == 2 ? 0.5 : 1;
	return (0);
}

int				mov_key_release(int kc, t_all *all)
{
	kc == 2 ? all->btn.mr = 0 : 0;
	kc == 0 ? all->btn.ml = 0 : 0;
	kc == 13 ? all->btn.mf = 0 : 0;
	kc == 1 ? all->btn.mb = 0 : 0;
	kc == 123 ? all->btn.rl = 0 : 0;
	kc == 124 ? all->btn.rr = 0 : 0;
	kc == 126 ? all->btn.ru = 0 : 0;
	kc == 125 ? all->btn.rd = 0 : 0;
	kc == 256 ? all->btn.walk = 1 : 0;
	if (all->btn.walk == 2 && kc == 35)
		all->btn.pause = all->btn.pause == 2 ? 1 : 3;
	return (0);
}

void			mov_avoid_collision(t_all *all, t_plr *p, char **m)
{
	mov_calc_plr_square(p);
	if ((m[(int)p->yad][(int)p->xab] == '1'
	&& m[(int)p->yad][(int)p->xcd] == '1')
	|| (m[(int)p->yad][(int)p->x] == '1'))
		p->y += (int)p->y - p->yad;
	mov_calc_plr_square(p);
	if ((m[(int)p->ybc][(int)p->xab] == '1'
	&& m[(int)p->yad][(int)p->xab] == '1')
	|| (m[(int)p->y][(int)p->xab] == '1'))
		p->x -= p->xab - (int)p->xab;
	mov_calc_plr_square(p);
	if ((m[(int)p->ybc][(int)p->xcd] == '1'
	&& m[(int)p->ybc][(int)p->xab] == '1')
	|| (m[(int)p->ybc][(int)p->x] == '1'))
		p->y -= p->ybc - (int)p->ybc;
	mov_calc_plr_square(p);
	if ((m[(int)p->yad][(int)p->xcd] == '1'
	&& m[(int)p->ybc][(int)p->xcd] == '1')
	|| (m[(int)p->y][(int)p->xcd] == '1'))
		p->x += (int)p->x - p->xcd;
}

void			mov_key_rotation_angles(t_all *all, t_plr *p, float k)
{
	if (all->btn.rl == 1)
		p->dir -= p->kbratio;
	if (all->btn.rr == 1)
		p->dir += p->kbratio;
	mov_check_rotate(all);
	p->sind = sin(p->dir) * k;
	p->cosd = cos(p->dir) * k;
	p->sindp2 = sin(p->dir + M_PI_2) * k;
	p->cosdp2 = cos(p->dir + M_PI_2) * k;
}

void			mov_key(t_all *all, char **m, t_plr *p)
{
	float		k;

	k = all->btn.walk2 * SPEED / all->btn.walk;
	mov_key_rotation_angles(all, p, k);
	mov_key2(all, m, p, k);
	mov_avoid_collision(all, p, m);
}

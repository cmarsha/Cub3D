/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:39:25 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/17 21:39:43 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	return (0);
}

void			mov_check_rotate(t_all *all)
{
	if (all->plr.dir > 2 * M_PI)
		all->plr.dir -= 2 * M_PI;
	else if (all->plr.dir < 0)
		all->plr.dir += 2 * M_PI;
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

	k = SPEED / all->btn.walk;
	mov_key_rotation_angles(all, p, k);
	if (all->btn.mf == 1 && m[(int)(p->y + p->sind * IND)][(int)p->x] != '1')
		p->y += p->sind;
	if (all->btn.mf == 1 && m[(int)p->y][(int)(p->x + p->cosd * IND)] != '1')
		p->x += p->cosd;
	if (all->btn.mb == 1 && m[(int)(p->y - p->sind * IND)][(int)p->x] != '1')
		p->y -= p->sind;
	if (all->btn.mb == 1 && m[(int)p->y][(int)(p->x - p->cosd * IND)] != '1')
		p->x -= p->cosd;
	if (all->btn.mr == 1 && m[(int)(p->y + p->sindp2 * IND)][(int)p->x] != '1')
		p->y += p->sindp2;
	if (all->btn.mr == 1 && m[(int)p->y][(int)(p->x + p->cosdp2 * IND)] != '1')
		p->x += p->cosdp2;
	if (all->btn.ml == 1 && m[(int)(p->y - p->sindp2 * IND)][(int)p->x] != '1')
		p->y -= p->sindp2;
	if (all->btn.ml == 1 && m[(int)p->y][(int)(p->x - p->cosdp2 * IND)] != '1')
		p->x -= p->cosdp2;
}

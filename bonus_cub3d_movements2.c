/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_movements2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:03:58 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/18 23:04:05 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

void			mov_calc_plr_square(t_plr *p)
{
	p->xab = p->x + PSIZE;
	p->yad = p->y - PSIZE;
	p->ybc = p->y + PSIZE;
	p->xcd = p->x - PSIZE;
}

void			mov_check_rotate(t_all *all)
{
	if (all->plr.dir > 2 * M_PI)
		all->plr.dir -= 2 * M_PI;
	else if (all->plr.dir < 0)
		all->plr.dir += 2 * M_PI;
}

void			mov_mouse(t_all *all)
{
	int		turn;
	int		incline;

	mlx_mouse_get_pos(all->wind, &all->mous.x, &all->mous.y);
	turn = all->mous.x - all->par.hrx;
	all->plr.dir += turn * all->plr.ratio;
	mov_check_rotate(all);
	incline = all->mous.y - all->par.hry;
	if (all->par.horizont < all->par.ry && all->par.horizont > 0)
		all->par.horizont -= incline * all->plr.sens;
	if (all->par.horizont >= all->par.ry)
	{
		all->par.horizont = all->par.ry;
		all->par.horizont -= incline > 0 ? abs(incline) * all->plr.sens : 0;
	}
	if (all->par.horizont <= 0)
	{
		all->par.horizont = 0;
		all->par.horizont += incline < 0 ? abs(incline) * all->plr.sens : 0;
	}
	turn || incline ? all->btn.smth = 1 : 0;
	all->btn.pause == 0 ? mlx_mouse_move(all->wind, all->par.hrx, all->par.hry
		- all->mous.fckn) : 0;
}

void			mov_key2(t_all *all, char **m, t_plr *p, float k)
{
	if ((all->btn.mf == 1 && m[(int)(p->y + p->sind * IND)][(int)p->x] != '1')
	&& (all->btn.mf == 1 && m[(int)(p->y + p->sind * IND)][(int)p->x] != '2'))
		p->y += p->sind;
	if ((all->btn.mf == 1 && m[(int)p->y][(int)(p->x + p->cosd * IND)] != '1')
	&& (all->btn.mf == 1 && m[(int)p->y][(int)(p->x + p->cosd * IND)] != '2'))
		p->x += p->cosd;
	if ((all->btn.mb == 1 && m[(int)(p->y - p->sind * IND)][(int)p->x] != '1')
	&& (all->btn.mb == 1 && m[(int)(p->y - p->sind * IND)][(int)p->x] != '2'))
		p->y -= p->sind;
	if ((all->btn.mb == 1 && m[(int)p->y][(int)(p->x - p->cosd * IND)] != '1')
	&& (all->btn.mb == 1 && m[(int)p->y][(int)(p->x - p->cosd * IND)] != '2'))
		p->x -= p->cosd;
	if ((all->btn.mr == 1 && m[(int)(p->y + p->sindp2 * IND)][(int)p->x] != '1')
	&& (all->btn.mr == 1 && m[(int)(p->y + p->sindp2 * IND)][(int)p->x] != '2'))
		p->y += p->sindp2;
	if ((all->btn.mr == 1 && m[(int)p->y][(int)(p->x + p->cosdp2 * IND)] != '1')
	&& (all->btn.mr == 1 && m[(int)p->y][(int)(p->x + p->cosdp2 * IND)] != '2'))
		p->x += p->cosdp2;
	if ((all->btn.ml == 1 && m[(int)(p->y - p->sindp2 * IND)][(int)p->x] != '1')
	&& (all->btn.ml == 1 && m[(int)(p->y - p->sindp2 * IND)][(int)p->x] != '2'))
		p->y -= p->sindp2;
	if ((all->btn.ml == 1 && m[(int)p->y][(int)(p->x - p->cosdp2 * IND)] != '1')
	&& (all->btn.ml == 1 && m[(int)p->y][(int)(p->x - p->cosdp2 * IND)] != '2'))
		p->x -= p->cosdp2;
}

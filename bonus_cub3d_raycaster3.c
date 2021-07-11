/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_raycaster3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 18:02:32 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/21 18:02:34 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

void			draw_color_nums(t_color *col, int n)
{
	col->rnum = n;
	col->rden = n;
	col->gnum = n;
	col->gden = n;
	col->bnum = n;
	col->bden = n;
}

void			draw_shadow(t_color *col, float perp)
{
	col->rnum = 1;
	col->rden = perp;
	col->gnum = 1;
	col->gden = perp;
	col->bnum = 1;
	col->bden = perp;
}

unsigned		my_mlx_pixel_out(t_win *win, int x, int y)
{
	char		*dst;
	unsigned	color;

	dst = win->addr + (y * win->ll + x * (win->bpp / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void			my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (y * win->ll + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned char	my_rgb_manipulation(unsigned char rgb, float num, float den)
{
	float		tmp;

	tmp = (int)rgb * num / den;
	tmp = tmp > 255 ? 255 : tmp;
	tmp = tmp < 1 ? 1 : tmp;
	return (tmp);
}

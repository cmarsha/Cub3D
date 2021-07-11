/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 13:04:06 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/24 13:04:42 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

int				engine(t_all *all)
{
	t_btn		b;

	b = all->btn;
	if (all->btn.pause == 0)
	{
		all->mous.fckn == 0 ? mov_mouse_offset(all) : 0;
		mov_key(all, all->map.map, &all->plr);
		mov_mouse(all);
		mlx_mouse_hide();
	}
	mlx_do_sync(all->mlx);
	engine_pause(all);
	if ((b.mb || b.mf || b.ml || b.mr || b.rl || b.rr || b.ru || b.rd ||
		b.j > 0 || b.smth) && all->btn.pause != 2)
	{
		raycaster(all);
		all->btn.smth = 0;
		mlx_put_image_to_window(all->mlx, all->wind, all->win[0].img, 0, 0);
	}
	return (0);
}

void			my_mlx(t_all *all)
{
	if (!(all->win[0].img = mlx_new_image(all->mlx, all->par.rx, all->par.ry)))
		errormsg(4, "Function mlx_new_image() failed!");
	if (!(all->win[0].addr = mlx_get_data_addr(all->win[0].img,
		&all->win[0].bpp, &all->win[0].ll, &all->win[0].en)))
		errormsg(4, "Function mlx_get_data_addr() failed!");
	spr_allocation(all);
	raycaster(all);
	(all->save == 1) ? screenshot(all) : (all->wind = mlx_new_window(all->mlx,
		all->par.rx, all->par.ry, "cub3D"));
	mlx_put_image_to_window(all->mlx, all->wind, all->win[0].img, 0, 0);
	mlx_hook(all->wind, 2, 1L << 0, mov_key_press, all);
	mlx_hook(all->wind, 3, 1L << 1, mov_key_release, all);
	mlx_hook(all->wind, 17, 1L << 0, exit_cross, all);
	mlx_loop_hook(all->mlx, engine, all);
	mlx_loop(all->mlx);
}

int				main(int argc, char **argv)
{
	t_list	*head;
	t_all	all;

	check_input_params(&all, argc, argv, &head);
	start_nullstr(&all);
	if (!(all.mlx = mlx_init()))
		errormsg(4, "Function mlx_init() failed!");
	parser(&all, head);
	start_params_count(&all);
	my_mlx(&all);
	return (0);
}

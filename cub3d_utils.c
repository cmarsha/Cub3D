/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:08:37 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/29 01:08:57 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			start_nullstr(t_all *all)
{
	int		i;

	i = 0;
	all->sprcount = 0;
	while (i < 6)
		ft_bzero(&all->win[i++], 10);
	ft_bzero(&all->par, 10);
	ft_bzero(&all->plr, 104);
	all->plr.dir = 99;
	ft_bzero(&all->txs, 80);
	ft_bzero(&all->btn, 60);
	all->btn.walk2 = 1;
	ft_bzero(&all->mous, 20);
	all->btn.walk = 1;
}

void			errormsg(int errornr, char *text)
{
	ft_putstr("Error\n");
	ft_putnbr(errornr);
	ft_putstr(", ");
	if (errornr == 9 || errornr == 15)
	{
		ft_putstr("File ");
		ft_putstr(text);
		errornr == 9 ? ft_putstr(" opening failed!\n") :
			ft_putstr(" closing failed!\n");
	}
	else
		ft_putstr(text);
	ft_putchar('\n');
	exit(errornr);
}

int				checkgnl(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void			check_texture_files(t_all *all, char *filename, t_win *w)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (ft_strcmp(&filename[ft_strlen(filename) - 4], ".xpm"))
		errormsg(88, "Texture file extension should be .xpm!");
	if ((fd = open(filename, O_RDONLY)) == -1)
		errormsg(9, filename);
	if (!(w->img = mlx_xpm_file_to_image(all->mlx, filename, &w->x, &w->y)))
		errormsg(78, "Not correct texture file!");
	if (!(w->addr = mlx_get_data_addr(w->img, &w->bpp, &w->ll, &w->en)))
		errormsg(343, "Function mlx_get_data_addr() failed!");
	if (close(fd))
		errormsg(15, filename);
}

void			res_check(t_all *all)
{
	int		x;
	int		y;

	mlx_get_screen_size(all->mlx, &x, &y);
	if (!all->save)
	{
		if (all->par.rx < 320 || all->par.ry < 200)
		{
			all->par.rx = all->par.rx < 320 ? 320 : all->par.rx;
			all->par.ry = all->par.ry < 200 ? 200 : all->par.ry;
		}
		if (all->par.rx > x || all->par.ry > y)
		{
			all->par.rx = all->par.rx > x ? x : all->par.rx;
			all->par.ry = all->par.ry > y ? y - 45 : all->par.ry;
			ft_putstr("Resolution of this screen is ");
			ft_putnbr(x);
			ft_putstr(" x ");
			ft_putnbr(y);
			ft_putstr("!\n");
		}
	}
}

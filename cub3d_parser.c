/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:39:40 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/29 19:39:47 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		pars_res(t_all *all, char *temp, int power)
{
	int		i;
	int		n;

	n = 0;
	i = 1;
	if (((all->par.pars_done >> power) & 1) == 1)
		errormsg(6, "Recurring resolution parameter!");
	while (temp[i] == ' ')
		i++;
	i = mini_atoi(&all->par.rx, temp, i);
	while (temp[i] == ' ')
		i++;
	n = 0;
	i = mini_atoi(&all->par.ry, temp, i);
	if ((temp[i]) != '\0' || all->par.ry > 16384 || all->par.rx > 16384)
		errormsg(5, "Map resolution error!");
	all->par.pars_done += pow(2, power);
	res_check(all);
	if (!(all->par.perp = ft_calloc(all->par.rx + 1, sizeof(int))))
		errormsg(16, "Couldn't allocate memory for Z_BUFFER!");
}

void		pars_txs(t_all *all, char *temp, char **filename, int power)
{
	if (temp[0] == 'S')
	{
		if (temp[1] == ' ')
			power++;
		else if (temp[1] != 'O')
			errormsg(11, "Map error!");
	}
	temp += power == 5 ? 1 : 2;
	temp[0] == ' ' ? 0 : errormsg(11, "Map error!");
	while (*((char *)temp) == ' ')
		temp = (char *)temp + 1;
	*filename = (char *)temp;
	if (((all->par.pars_done >> power) & 1) == 1)
		errormsg(6, "Recurring texture parameters!");
	check_texture_files(all, *filename, &all->win[power]);
	all->par.pars_done += pow(2, power);
}

int			pars_int_color(char *temp, int *color, int shift)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	i = mini_atoi(&n, temp, i);
	if (n > 255 || (shift > 0 && (temp[i] != ',')))
		errormsg(7, "Color error!");
	*color += n << shift;
	return (i);
}

void		pars_color(t_all *all, char *temp, int *color, int power)
{
	int		i;

	i = 1;
	if (((all->par.pars_done >> power) & 1) == 1)
		errormsg(6, "Recurring color parameters!");
	while (temp[i] == ' ')
		i++;
	ft_isdigit(temp[i]) ? i += pars_int_color(&temp[i], color, 16) :
		errormsg(7, "Color error!");
	i++;
	while (temp[i] == ' ')
		i++;
	ft_isdigit(temp[i]) ? i += pars_int_color(&temp[i], color, 8) :
		errormsg(7, "Color error!");
	i++;
	while (temp[i] == ' ')
		i++;
	ft_isdigit(temp[i]) ? i += pars_int_color(&temp[i], color, 0) :
		errormsg(7, "Color error!");
	if (temp[i] != '\0')
		errormsg(7, "Color error!");
	all->par.pars_done += pow(2, power);
}

void		parser(t_all *all, t_list *gnl)
{
	char	*tmp;

	while (all->par.pars_done < 255 && gnl->next != NULL)
	{
		tmp = strtrim_free(gnl);
		if (tmp[0] == 'R' && tmp[1] == ' ')
			pars_res(all, tmp, 0);
		else if (tmp[0] == 'W' && tmp[1] == 'E')
			pars_txs(all, tmp, &all->txs.we, 1);
		else if (tmp[0] == 'N' && tmp[1] == 'O')
			pars_txs(all, tmp, &all->txs.no, 2);
		else if (tmp[0] == 'E' && tmp[1] == 'A')
			pars_txs(all, tmp, &all->txs.ea, 3);
		else if (tmp[0] == 'S')
			pars_txs(all, tmp, tmp[1] == 'O' ? &all->txs.so : &all->txs.s, 4);
		else if (tmp[0] == 'F' && tmp[1] == ' ')
			pars_color(all, tmp, &all->txs.f, 6);
		else if (tmp[0] == 'C' && tmp[1] == ' ')
			pars_color(all, tmp, &all->txs.c, 7);
		else if (tmp[0] != '\0' && all->par.pars_done != 255)
			errormsg(11, "Map error!");
		gnl = gnl->next;
		gnl->next == NULL ? errormsg(11, "Map error!") : 0;
		all->par.pars_done == 255 ? map_continuity(all, gnl) : 0;
	}
}

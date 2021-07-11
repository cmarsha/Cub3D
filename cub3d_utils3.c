/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:37:51 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/17 21:38:08 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			exit_cross(void)
{
	exit(0);
}

void		mov_mouse_offset(t_all *all)
{
	mlx_mouse_move(all->wind, all->par.hrx, all->par.hry);
	mlx_mouse_get_pos(all->wind, &all->mous.x, &all->mous.fckn);
	all->mous.fckn = all->par.hry - all->mous.fckn;
	mlx_mouse_move(all->wind, all->par.hrx, all->par.hry - all->mous.fckn);
}

int			mini_atoi(int *num, char *temp, int i)
{
	int		n;

	n = 0;
	while (temp[i] == '0')
		i++;
	while (ft_isdigit(temp[i]) && n++ < 5)
		*num = *num * 10 + ((temp[i++]) - 48);
	return (i);
}

void		start_params_count(t_all *all)
{
	all->plr.sens = (float)SENS / 5;
	all->plr.ratio = all->plr.sens * M_PI_2 / 1000;
	all->plr.kbratio = all->plr.ratio * 50;
	all->par.nrx = all->par.rx;
	if ((all->par.ratio = (float)all->par.rx / (float)all->par.ry) > 1.85)
		all->par.rx = all->par.ry * 1.7;
	all->par.hnrx = all->par.nrx / 2;
	all->plr.step = (M_PI / 3) / all->par.rx;
	all->par.hrx = all->par.rx / 2;
	all->par.hry = all->par.ry / 2;
	all->par.horizont = (float)all->par.hry;
}

void		check_input_params(t_all *all, int argc, char **argv, t_list **head)
{
	int		fd;
	char	*line;
	int		maplen;
	int		gnl;

	if (argc < 2 || argc > 3)
		errormsg(1, "Too few of too many arguments!");
	if ((maplen = ft_strlen(argv[1])) < 5 || ft_strcmp(&argv[1][maplen - 4],
		".cub"))
		errormsg(2, "Map file  should be in format *.cub!");
	if (argc == 3 && !(all->save = ft_strcmp(argv[2], "--save") ? 0 : 1))
		errormsg(3, "Incorrect argument");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		errormsg(9, argv[1]);
	line = 0;
	while ((gnl = get_next_line(fd, &line)))
		ft_lstadd_back(head, ft_lstnew(line));
	gnl < 0 ? errormsg(4, "Function get_next_line() failed!") :
		ft_lstadd_back(head, ft_lstnew(line));
	if (ft_lstsize(*head) < 11)
		errormsg(11, "Map error!");
	if (close(fd))
		errormsg(15, argv[1]);
}

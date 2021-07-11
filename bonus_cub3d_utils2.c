/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_cub3d_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:27:09 by cmarsha           #+#    #+#             */
/*   Updated: 2021/02/15 21:27:12 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus_cub3d.h"

void			screenshot_header(t_all *all, unsigned char *head, int size)
{
	ft_bzero(head, 54);
	head[0] = 'B';
	head[1] = 'M';
	head[2] = size;
	head[3] = size >> 8;
	head[4] = size >> 16;
	head[5] = size >> 24;
	head[10] = 54;
	head[14] = 40;
	head[18] = all->par.rx;
	head[19] = all->par.rx >> 8;
	head[20] = all->par.rx >> 16;
	head[21] = all->par.rx >> 24;
	head[22] = -all->par.ry;
	head[23] = -all->par.ry >> 8;
	head[24] = -all->par.ry >> 16;
	head[25] = -all->par.ry >> 24;
	head[26] = 1;
	head[28] = 32;
}

void			screenshot(t_all *all)
{
	unsigned char	head[54];
	int				i;
	int				fd;
	int				size;
	int				bytes;

	size = 54 + all->par.ry * all->par.rx * all->win[0].bpp / 8;
	screenshot_header(all, head, size);
	i = -1;
	if ((fd = open("screenshot.bmp", O_RDWR | O_TRUNC | O_CREAT | O_APPEND,
																0755)) == -1)
		errormsg(9, "screenshot.bmp");
	bytes = all->win[0].bpp / 8 * all->par.rx;
	write(fd, head, 54);
	while (++i < all->par.ry)
		write(fd, &all->win[0].addr[i * all->win[0].ll], bytes);
	if (close(fd))
		errormsg(15, "screenshot.bmp");
	ft_putstr("You may see your screenshot.bmp!\n");
	exit(0);
}

char			*strtrim_free(t_list *gnl)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = gnl->content;
	while (tmp[i] != '\0')
	{
		if (tmp[i++] != ' ')
		{
			if (!(gnl->content = ft_strtrim(gnl->content, " ")))
				errormsg(17, "Function ft_strtrim() failed!");
			free(tmp);
			return (gnl->content);
		}
	}
	return (gnl->content);
}

void			map_elem_check(char m)
{
	if (!(m == '0' || m == '1' || m == '2' || m == 'N'
		|| m == 'S' || m == 'E' || m == 'W'))
		errormsg(11, "Map error!");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 13:04:46 by cmarsha           #+#    #+#             */
/*   Updated: 2021/01/24 13:05:37 by cmarsha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_CUB3D_H
# define BONUS_CUB3D_H
# define SCALE 10
# define SPEED 0.15
# define SENS 10
# define IND 1.5
# define RAY_MAP_COLOR 0xFF6600
# define MAP_COLOR 0x201005
# define MAP_SPR_COLOR 0x0000FF
# define MAP_ASPR_COLOR 0xEFFD5F
# define RAY_MAP_STEP 4
# define M_PI_6 M_PI / 6
# define EA 0
# define SO M_PI_2
# define WE M_PI
# define NO 3 * M_PI_2
# define RAY_STEP 0.002
# define PSIZE 0.3

# include <fcntl.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# define _USE_MATH_DEFINES
# include <math.h>

typedef struct		s_win
{
	void			*img;
	void			*addr;
	int				bpp;
	int				ll;
	int				en;
	int				x;
	int				y;
}					t_win;

typedef struct		s_par
{
	int				rx;
	int				ry;
	int				hrx;
	int				hry;
	int				nrx;
	int				hnrx;
	float			ratio;
	int				color;
	int				pars_done;
	float			horizont;
	int				wt;
	int				wn;
	float			*perp;
}					t_par;

typedef	struct		s_txs
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				c;
	int				f;
}					t_txs;

typedef struct		s_spr
{
	int				n;
	int				x;
	int				y;
	float			fx;
	float			fy;
	float			d;
	int				h;
	float			sty;
	float			stx;
	float			a;
	float			b;
	int				cx;
	int				sx;
	int				ex;
	float			px;
	float			py;
	int				top;
	int				stop;
	int				btm;
	int				alwd;
}					t_spr;

typedef struct		s_map
{
	char			**map;
	int				wide;
	int				height;
}					t_map;

typedef struct		s_plr
{
	float			x;
	float			y;
	float			xab;
	float			xcd;
	float			yad;
	float			ybc;
	float			dir;
	float			ratio;
	float			kbratio;
	float			step;
	float			incline;
	float			start;
	float			sind;
	float			cosd;
	float			sindp2;
	float			cosdp2;
	float			end;
	float			sens;
}					t_plr;

typedef struct		s_btn
{
	int				rl;
	int				rr;
	int				ru;
	int				rd;
	int				mf;
	int				mb;
	int				mr;
	int				ml;
	int				j;
	int				d;
	int				count;
	int				smth;
	int				walk;
	int				pause;
	float			walk2;
}					t_btn;

typedef struct		s_mous
{
	int				x;
	int				y;
	int				fckn;
}					t_mous;

typedef struct		s_color
{
	float			rnum;
	float			rden;
	float			gnum;
	float			gden;
	float			bnum;
	float			bden;
}					t_color;

typedef struct		s_raycast
{
	float			co;
	float			si;
}					t_raycast;

typedef struct		s_all
{
	t_win			win[7];
	t_par			par;
	t_txs			txs;
	t_spr			*spr;
	t_map			map;
	t_plr			plr;
	t_btn			btn;
	t_mous			mous;
	t_color			col;
	t_raycast		r;
	void			*mlx;
	void			*wind;
	int				sprcount;
	int				save;
}					t_all;

void				map_elem_check(char m);
void				map_elem_pars(t_all *all, char m, int x, int y);
void				map_check(t_all *all, int j);
void				map_make(t_all *all, t_list **head, int size);
void				map_continuity(t_all *all, t_list *head);
void				errormsg(int errornr, char *text);
int					checkgnl(char *line);
void				check_texture_files(t_all *all, char *filename, t_win *w);
void				pars_res(t_all *all, char *temp, int par_weight);
void				pars_txs(t_all *all, char *temp, char **filename, \
			int par_weight);
int					pars_int_color(char *temp, int *color, int shift);
void				pars_color(t_all *all, char *temp, int *color, \
			int par_weight);
void				parser(t_all *all, t_list *tmp);
char				*strtrim_free(t_list *lst);
void				res_check(t_all *all);
void				screenshot_header(t_all *all, unsigned char *head, \
			int size);
void				screenshot(t_all *all);
void				draw_map_rays(t_all *all, t_plr *r);
void				draw_map_backgroung(t_all *all);
void				draw_map(t_all *all);
void				engine_pause(t_all *all);
void				draw_black(t_all *all, t_spr *w, int *x);
void				draw_color_nums(t_color *col, int n);
void				draw_shadow(t_color *col, float perp);
unsigned			my_mlx_pixel_out(t_win *win, int x, int y);
void				my_mlx_pixel_put(t_win *win, int x, int y, int color);
unsigned char		my_rgb_manipulation(unsigned char rgb, float num, \
			float den);
unsigned			my_mlx_pixel(t_win *win, int x, int y, t_color *col);
void				draw_tex_y(t_all *all, t_spr *w, int x, int texn);
void				draw_calc_top_btm(t_all *all, t_spr *w);
int					draw_wall_raycasting(t_all *all, t_plr *ray, t_raycast *r);
void				draw_wall_cast_rays(t_all *all, t_plr *ray, t_spr *w, \
			int x);
void				draw_wall_counting_x(t_all *all, t_plr *ray, t_spr *w, \
			int x);
void				draw_spr_tex_x(t_all *all, int i, int x);
void				draw_spr(t_all *all);
void				draw_walls(t_all *all);
void				raycaster(t_all *all);
void				spr_angles_quadrants(t_all *all, int i);
void				spr_params_counting(t_all *all, int i);
void				spr_get_allowed(t_all *all);
void				spr_sorting(t_all *all);
void				spr_allocation(t_all *all);
void				mov_calc_plr_square(t_plr *p);
void				mov_check_rotate(t_all *all);
void				mov_mouse_offset(t_all *all);
void				mov_mouse(t_all *all);
void				mov_key2(t_all *all, char **m, t_plr *p, float k);
int					mov_key_press(int kc, t_all *all);
int					mov_key_release(int kc, t_all *all);
void				mov_avoid_collision(t_all *all, t_plr *p, char **m);
void				mov_key_rotation_angles(t_all *all, t_plr *p, float k);
void				mov_key(t_all *all, char **m, t_plr *p);
int					exit_cross(void);
int					mini_atoi(int *num, char *temp, int i);
int					engine(t_all *all);
void				my_mlx(t_all *all);
void				start_params_count(t_all *all);
void				start_nullstr(t_all *all);
void				check_input_params(t_all *all, int argc, char **argv, \
			t_list **head);

#endif

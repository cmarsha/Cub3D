# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmarsha <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:42:48 by cmarsha           #+#    #+#              #
#    Updated: 2020/12/26 22:20:52 by cmarsha          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
MLX = libmlx.dylib
LIBFT = libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -framework OpenGL -framework Appkit
HEADERF = cub3d.h bonus_cub3d.h
CFILES = cub3d.c cub3d_parser.c cub3d_utils.c cub3d_map.c cub3d_utils2.c \
		cub3d_raycaster.c cub3d_sprites.c cub3d_movements.c cub3d_utils3.c \
		cub3d_raycaster2.c
BFILES = bonus_cub3d.c bonus_cub3d_parser.c bonus_cub3d_utils.c \
		bonus_cub3d_map.c bonus_cub3d_utils2.c bonus_cub3d_raycaster.c \
		bonus_cub3d_sprites.c bonus_cub3d_movements.c bonus_cub3d_utils3.c \
		bonus_cub3d_movements2.c bonus_cub3d_raycaster2.c \
		bonus_cub3d_raycaster3.c bonus_cub3d_raycaster4.c
OBJ := $(CFILES:.c=.o)
BOBJ := $(BFILES:.c=.o)

.PHONY: all clean fclean re run deb debb win save mlxx lin w s

all: $(MLX) $(NAME)

%.o : %.c $(HEADERF)
	$(CC) -c $< -o $@
		
$(MLX):
	$(MAKE) -C mlx
	mv mlx/$(MLX) .

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

bonus: $(MLX) $(LIBFT) $(BOBJ)
	$(CC) $(BOBJ) $(CFLAGS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

clean:
	/bin/rm -f $(OBJ) $(BOBJ)
	$(MAKE) clean -C mlx
	$(MAKE) clean -C libft

fclean: clean
	/bin/rm -f $(MLX)
	/bin/rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

w:
	./cub3D map.cub

s:
	./cub3D map.cub --save

run:
	$(CC) $(CFLAGS) -o main *.c
	./main

deb:
	$(CC) $(CFLAGS) -g *.c libft/*.c
	./a.out map.cub

debb:
	$(CC) -o main -g *d.c libft/*.c
	./main map.cub

win:
	$(CC) -o win.out -g $(CFILES) libft/*.c libmlx.dylib -framework OpenGL -framework Appkit
	./win.out map.cub

save:
	$(CC) $(CFLAGS) -o win.out $(CFILES) libft/*.c libmlx.dylib -framework OpenGL -framework Appkit
	./win.out map.cub --save

mlxx:
	$(CC) -o wind.out mlx.c libft/*.c libmlx.dylib -framework OpenGL -framework Appkit
	./wind.out

lin:
	$(CC) -o lin.out cub3d.c cub3d_parser.c cub3d_utils.c cub3d_utils2.c cub3d_map.c libft/*.c -Lmlx_linux -lmlx_Linux -L/usr/local/lib -Imlx_linux -lXext -lX11 -lm
	./lin.out map.cub
# -lz
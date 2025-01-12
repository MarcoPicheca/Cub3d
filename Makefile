NAME = cub3D

SRC =	src/main.c \
		src/args_check.c \
		src/gen_map.c \
		src/get_next_line.c \
		src/free_all.c \
		src/check_map_game.c \
		src/check_map.c \
		src/flood_fill_check.c \
		src/check_rgb_f_c.c \
		src/check_crdls.c \
		src/mlx_callback_fts.c \
		src/map_init.c \
		src/movement.c \
		src/drawing_fts.c \
		src/render.c \
		src/game_init.c \
		src/raycast_3d.c src/wall2_xpm.c \
		src/draw_2d.c src/draw_3d.c src/utils_4_minilibx.c src/move_player.c \
		src/control.c src/get_color.c src/about_textures.c src/draw_minimap.c

LIBFT = ./libft/libft.a

MLX =  -Lminilibx-linux -lmlx -lX11 -lXext

CC = cc

MATH = -lm

CFLAGS = -Wall -Werror -Wextra -g 

all: $(NAME)

$(NAME): $(SRC)
	@make -sC libft
	@cd minilibx-linux && make
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(MLX) $(MATH) -o $(NAME)

# download repo minilib x 
download:
	@git clone https://github.com/42Paris/minilibx-linux.git
	@echo "Cloned minilibx"

# rm della minilibx da fare sempre prima del push 
rm_libx:
	@rm -rf minilibx-linux
	@echo "removed minilibx"

clean:
	@make clean -sC libft
	@cd minilibx-linux && make clean

fclean: clean
	@make fclean -sC libft
	rm $(NAME)

re: fclean all

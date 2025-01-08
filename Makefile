NAME = cub3D

SRC = src/main.c src/args_check.c src/gen_map.c src/get_next_line.c \
		src/free_all.c src/mlx_callback_fts.c src/raycast_3d.c src/wall2_xpm.c \
		src/draw_2d.c src/draw_3d.c src/utils_4_minilibx.c src/move_player.c \
		src/control.c src/get_color.c src/about_textures.c src/render.c

LIBFT = ./libft/libft.a

MLX =  -Lminilibx-linux -lmlx -lX11 -lXext

CC = cc

CFLAGS = -g -lm -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	@make -sC libft
	@cd minilibx-linux && make
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(MLX) -lm -o $(NAME)

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

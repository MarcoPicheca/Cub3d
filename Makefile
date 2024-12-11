NAME = cub3D

SRC = src/main.c

LIBFT = ./libft/libft.a

MLX =  -Lminilibx-linux -lmlx -lX11 -lXext

CC = cc

CFLAGS = -g -lm -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC)
	@make -sC libft
	@cd minilibx-linux && make
	$(CC) $(CFLAGS) $(SRC) $(LIBFT) $(MLX) -o $(NAME)

download:
	@wget https://cdn.intra.42.fr/document/document/21656/minilibx-linux.tgz
	@tar -xf minilibx-linux.tgz
	@$(RM) minilibx-linux.tgz

clean:
	@make clean -sC libft
	@cd minilibx-linux && make clean

fclean: clean
	@make fclean -sC libft
	rm $(NAME)

re: fclean all

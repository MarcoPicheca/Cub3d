NAME = cub3D

BONUS_NAME = cub3D_bonus

SRC =	$(wildcard src/*.c)

BONUS_SRC = $(wildcard src_bonus/*.c)

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

bonus: CFLAGS += -DBONUS
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(SRC) $(BONUS_SRC)
	@make -sC libft
	@cd minilibx-linux && make
	$(CC) $(CFLAGS) $(SRC) $(BONUS_SRC) $(LIBFT) $(MLX) -o $(BONUS_NAME) $(MATH)

clean:
	@make clean -sC libft
	@cd minilibx-linux && make clean

fclean: clean
	@make fclean -sC libft
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus download rm_libx


NAME = wolf3d
FILES = main.c ft_map_read.c ft_image_operations.c ft_map_validation.c \
		ft_cast_ray.c ft_cast_ray_c.c ft_controls.c ft_controls_c.c \
		ft_key.c ft_menu.c ft_xpm_read.c ft_init.c \


SRC = $(addprefix srcs/, $(FILES))
FILESO = $(addprefix objectives/, $(FILES:.c=.o))
FLAGS = -Wall -Wextra -Werror
LIBA = -L ./libs/libft -lft
MIN = -L ./libs/minilibx_macos -lmlx
ADD = -framework OpenGL -framework AppKit
INCL = -I ./libs/libft -I ./libs/minilibx_macos -I .

all: $(NAME)

$(NAME): $(FILESO)
	make -C ./libs/libft/
	make -C ./libs/minilibx_macos/
	gcc $(FLAGS) -o $(NAME) $(SRC) $(INCL) $(LIBA) $(MIN) $(ADD)

objectives/%.o: srcs/%.c | objectives
	gcc $(FLAGS) $(INCL) -o $@ -c $<

clean:
	rm -rf objectives/
	make clean -C ./libs/libft/
	make clean -C ./libs/minilibx_macos/

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libs/libft/

objectives:
	mkdir objectives/

re: fclean all

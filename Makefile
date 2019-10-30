CC=gcc
CFLAGS=-Wall -Wextra -Werror
ENGINE_OBJS=$(addprefix engine/, input.o input_handlers.o input_handle_loop.o input_util.o screen.o screen2.o)
OBJS=main.o render.o map.o textures.o player.o entity.o entity_rendering.o ray_casting.o map_is_wall.o $(ENGINE_OBJS)
FRAMEWORKS=-framework OpenGL -framework AppKit
RM=rm -rf
LIBFT=libft
LIBMLX=minilibx_macos
LIBS=-L$(LIBFT) -lft -L$(LIBMLX) -lmlx
NAME=wolf3d

vpath libft.a $(LIBFT)
vpath libmlx.a $(LIBMLX)

all: $(NAME)

$(NAME): $(OBJS) -lft -lmlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(FRAMEWORKS) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make -sC $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -sC $(LIBFT) fclean
	make -sC $(LIBMLX) clean

re: fclean all

norme:
	norminette libft/*.[ch]
	norminette libft/ft_printf/*.[ch]
	norminette engine/*.[ch]
	norminette *.[ch]

.PHONY: all clean fclean re norme

$(LIBFT)/libft.a:
	make -sC $(LIBFT)

$(LIBMLX)/libmlx.a:
	make -sC $(LIBMLX)

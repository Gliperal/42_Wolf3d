CC=gcc
CFLAGS=
OBJS=main.o render.o map.o textures.o $(addprefix input/,input.o input_handlers.o input_handle_loop.o input_util.o) rendering/screen.o
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
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean
	make -C $(LIBMLX) clean

re: fclean all

.PHONY: all clean fclean re

$(LIBFT)/libft.a:
	make -C $(LIBFT)

$(LIBMLX)/libmlx.a:
	make -C $(LIBMLX)

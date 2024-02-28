INCLUDES = -I/usr/include -Imlx
# MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib/X11 -Imlx_linux -lXext -lX11 -lm -lz
MLX_FLAGS = -framework OpenGL -framework AppKit
NAME = so_long
C_FLAGS = -Wall -Werror -Wextra
MLX_MAC = ./mlx_mac
SRCS = DFS.c utils.c get_next_line.c map.c init_sprite_animated.c

LINUX_COMPILE = $(SRCS) ./mlx_linux/libmlx.a -lX11 -I X11 -lXext
COMPILE_ARGS = $(SRCS) $(MLX_FLAGS) libmlx.dylib
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	COMPILE_ARGS = $(LINUX_COMPILE)
endif

# test :
# 	cc $(C_FLAGS) init_sprite_animated.c $(COMPILE_ARGS) -g

all :
	make -C $(MLX_MAC)
	cp $(MLX_MAC)/libmlx.dylib .
	cc $(C_FLAGS) $(NAME).c $(COMPILE_ARGS) -g -o $(NAME)
	./$(NAME) maps/1.ber

DFS : re
	@rm -f DFS
	@cc $(C_FLAGS) DFS.c utils.c map.c get_next_line.c -g -o DFS

re : fclean all

.c.o :
	cc $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJS)
	cc $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean :
	rm -rf *.o

fclean : clean
	rm -rf $(NAME)

.PHONY : test all clean re fclean

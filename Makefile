INCLUDES = -I/usr/include -Imlx
# MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib/X11 -Imlx_linux -lXext -lX11 -lm -lz
MLX_FLAGS = -framework OpenGL -framework AppKit
NAME = so_long
C_FLAGS = -Wall -Werror -Wextra
MLX_MAC = ./mlx_mac


LINUX_COMPILE = cc -Wall -Werror -Wextra so_long.c mlx_linux/libmlx.a -lX11 utils.c get_next_line.c -I X11 -lXext -o so_long
COMPILE_ARGS = cc $(C_FLAGS) so_long.c get_next_line.c utils.c $(MLX_FLAGS) -o $(NAME) libmlx.dylib -g
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	COMPILE_ARGS = $(LINUX_COMPILE)
endif

DFS : re
	@rm -f DFS
	@cc $(C_FLAGS) DFS.c utils.c -g -o DFS
	@./DFS

re :
	@rm -rf $(NAME)

all :
	make -C $(MLX_MAC)
	cp $(MLX_MAC)/libmlx.dylib .
	$(COMPILE_ARGS)
	./$(NAME) maps/1.ber

.c.o :
	cc $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJS)
	cc $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean :
	rm -rf $(NAME)

.PHONY : $(NAME) test all clean re fclean

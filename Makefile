INCLUDES = -I/usr/include -Imlx
# MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib/X11 -Imlx_linux -lXext -lX11 -lm -lz
MLX_FLAGS = -framework OpenGL -framework AppKit
NAME = so_long
C_FLAGS = -Wall -Werror -Wextra
MLX_MAC = ./mlx_mac

all :
	make -C $(MLX_MAC)
	cp $(MLX_MAC)/libmlx.dylib .
	cc $(C_FLAGS) main.c $(MLX_FLAGS) -o $(NAME) libmlx.dylib -g

.c.o :
	cc $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJS)
	cc $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean :
	rm -rf $(NAME)

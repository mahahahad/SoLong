INCLUDES = -I/usr/include -Imlx
MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib/X11 -Imlx_linux -lXext -lX11 -lm -lz
NAME = so_long
C_FLAGS = -Wall -Werror -Wextra

all :
	cc $(C_FLAGS) main.c $(MLX_FLAGS) -o $(NAME) -g

.c.o :
	cc $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJS)
	cc $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

clean :
	rm -rf $(NAME)

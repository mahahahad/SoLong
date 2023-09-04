INCLUDES = -I/usr/include -Imlx
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
NAME = so_long
C_FLAGS = -Wall -Werror -Wextra

.c.o :
	cc $(C_FLAGS) -c -o $@ $< $(INCLUDES)

$(NAME) : $(OBJS)
	cc $(C_FLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

all :
	cc $(C_FLAGS) main.c $(MLX_FLAGS)


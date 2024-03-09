NAME = so_long
MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -I.
C_FLAGS = -Wall -Werror -Wextra

SRCS_DIR = src/
SRCS = args.c map.c render_utils.c render.c DFS.c enemy.c enemy_utils.c free.c init_sprite_animated.c init_textures.c init_structs.c handlers.c movement.c so_long.c

OBJS_DIR = $(SRCS_DIR)objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

UTILS_DIR = ./utils/
UTILS = $(addprefix $(UTILS_DIR), utils.a)

UNAME = $(shell uname -s)

ifeq ($(UNAME), Darwin)
	MLX_FLAGS += -framework OpenGL -framework AppKit 
endif

all : $(NAME)

$(NAME) : $(OBJS) $(UTILS)
	@echo ''
	cc $(C_FLAGS) $(OBJS) $(UTILS) $(MLX_FLAGS) -o $(NAME) 

debug : fclean $(UTILS)
	@echo ''
	cc $(C_FLAGS) -DOFFSET=0 -fsanitize=address $(addprefix $(SRCS_DIR), $(SRCS)) $(UTILS) $(MLX_FLAGS) -g3 -o $(NAME)

$(UTILS) :
	@make -C $(UTILS_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $< $(MLX_FLAGS) -o $@
	@echo -n '.'

re : fclean all

clean :
	@rm -rf *.o
	@rm -rf $(OBJS_DIR)
	@make -C $(UTILS_DIR) clean

fclean : clean
	@rm -rf $(NAME)
	@make -C $(UTILS_DIR) fclean 

.PHONY : all re clean fclean debug

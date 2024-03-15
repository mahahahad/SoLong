NAME = so_long
MLX_FLAGS = -Lmlx -lmlx
C_FLAGS = -Wall -Werror -Wextra -Iincludes

BGREEN = \033[1;32m
BYELLOW = \033[1;33m
BRED = \033[1;31m
BGGREEN = \033[0;102m
RESET = \033[0m\033[K

SRCS_DIR = src/
SRCS_BONUS_DIR = src_bonus/
SRCS = args.c map.c render_utils.c render.c DFS.c free.c init_textures.c init_structs.c handlers.c movement.c so_long.c
SRCS_BONUS = DFS_bonus.c args_bonus.c enemy_bonus.c enemy_utils_bonus.c free_bonus.c handlers_bonus.c init_sprite_animated_bonus.c init_structs_bonus.c init_textures_bonus.c map_bonus.c movement_bonus.c render_bonus.c render_utils_bonus.c so_long_bonus.c

OBJS_DIR = $(SRCS_DIR)objs/
OBJS_BONUS_DIR = $(SRCS_BONUS_DIR)objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
OBJS_BONUS = $(addprefix $(OBJS_BONUS_DIR), $(SRCS_BONUS:.c=.o))

UTILS_DIR = utils/
UTILS = $(addprefix $(UTILS_DIR), utils.a)

UNAME = $(shell uname -s)

ifeq ($(UNAME), Darwin)
	MLX_FLAGS += -framework OpenGL -framework AppKit
else
	MLX_FLAGS += -lX11 -lXext
endif

all : $(NAME)

$(NAME) : $(UTILS) $(OBJS)
	@printf "$(BYELLOW)Compiling $(NAME)\r$(RESET)"
	@cc $(C_FLAGS) $(OBJS) $(UTILS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(BGREEN)Created $(NAME)!$(RESET)"

debug : fclean $(UTILS)
	@cc $(C_FLAGS) -fsanitize=address $(addprefix $(SRCS_DIR), $(SRCS)) $(UTILS) $(MLX_FLAGS) -g3 -o $(NAME)
	@echo "$(BGREEN)Created $(BGGREEN)$(BYELLOW)DEBUG$(RESET) $(BGREEN)$(NAME)!$(RESET)"

$(UTILS) :
	@printf "$(BYELLOW)Compiling Utils Library\n\r$(RESET)"
	@make -C $(UTILS_DIR) -s

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $< -o $@
	@printf "%c\r" "|"
	@printf "%c\r" "/"
	@printf "%c\r" "—"
	@printf "%c\r" "\\"

$(OBJS_BONUS_DIR)%.o : $(SRCS_BONUS_DIR)%.c
	@mkdir -p $(OBJS_BONUS_DIR)
	@cc $(C_FLAGS) -c $< -o $@
	@printf "%c\r" "|"
	@printf "%c\r" "/"
	@printf "%c\r" "—"
	@printf "%c\r" "\\"

re : fclean all

clean :
	@echo "$(BRED)Removing object files$(RESET)"
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_BONUS_DIR)
	@make -C $(UTILS_DIR) -s clean

fclean : clean
	@echo "$(BRED)Removing executable$(RESET)"
	@make -C $(UTILS_DIR) -s fclean
	@rm -rf $(NAME)
	@rm -rf $(NAME)_bonus

bonus: $(UTILS) $(OBJS_BONUS)
	@printf "$(BYELLOW)Compiling $(NAME)_bonus\r$(RESET)"
	@cc $(C_FLAGS) $(OBJS_BONUS) $(UTILS) $(MLX_FLAGS) -o $(NAME)_bonus
	@echo "$(BGREEN)Created $(NAME)$(BGGREEN)_bonus!$(RESET)"

.PHONY : all re clean fclean debug bonus

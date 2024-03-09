NAME = utils.a
C_FLAGS = -Wall -Werror -Wextra

BGREEN = \033[1;32m
BYELLOW = \033[1;33m
RESET = \033[0m\033[K

SRCS = ft_bzero.c ft_calloc.c ft_error.c ft_itoa.c ft_putnbr.c ft_putstr.c ft_putstr_endl.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_substr.c get_next_line.c ft_make_2d_arr.c ft_free_2d_arr.c 

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@echo "$(BGREEN)Created Utils Library$(RESET)"

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $< -o $@
	@printf "%c\r" "|"
	@printf "%c\r" "/"
	@printf "%c\r" "—"
	@printf "%c\r" "\\"

clean :
	rm -rf objs *.o

fclean : clean
	rm -f utils.a

re : fclean all

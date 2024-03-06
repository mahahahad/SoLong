NAME = utils.a
C_FLAGS = -Wall -Werror -Wextra
SRCS = ft_bzero.c ft_calloc.c ft_error.c ft_itoa.c ft_putnbr.c ft_putstr.c ft_putstr_endl.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_substr.c get_next_line.c ft_make_2d_arr.c ft_free_2d_arr.c 
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "\nCreated Library"
	@ar -rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o : %.c
	@mkdir -p $(OBJS_DIR)
	@cc $(C_FLAGS) -c $< -o $@
	@echo -n '.'

clean :
	rm -rf objs *.o

fclean : clean
	rm -f utils.a

re : fclean all

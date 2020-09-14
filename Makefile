SRC		= ft_printf.c conv_num.c conv_other.c conv_util.c flag.c ft_printf.c\
			parsing.c print.c print_util.c util.c
OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -g #

NAME	= libftprintf.a

a.out 	: test.o $(NAME)
		$(CC) $(CFLAGS) test.o $(NAME)

$(NAME) : $(NAME)($(OBJ))

.PHONY	: re clean fclean all

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) *.o

re		: fclean  all

all		: $(NAME)

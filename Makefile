SRC		= ft_printf.c
OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -O3 -fsanitize=address

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

SRC		= ft_printf.c conv_num.c conv_other.c conv_util.c flag.c ft_printf.c\
			parsing.c print.c print_util.c
OBJ		= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -g 

NAME	= libftprintf.a
ifeq  '$(shell ar V 2>/dev/null | head -c 3)' 'GNU'
	ARFLAGS	= Ur
endif

$(NAME) : $(NAME)($(OBJ))

.PHONY	: re clean fclean all

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) *.o

re		: fclean  all

all		: $(NAME)

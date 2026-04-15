##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## c
##

SRC	=	my_compute_power_rec.c	\
		my_compute_square_root.c	\
		my_find_prime_sup.c	\
		my_getnbr.c	\
		my_isneg.c	\
		my_is_prime.c	\
		my_putchar.c	\
		my_put_nbr.c	\
		my_putstr.c	\
		my_revstr.c	\
		my_showmem.c	\
		my_showstr.c	\
		my_sort_int_array.c	\
		my_strcapitalize.c	\
		my_strcat.c	\
		my_strcmp.c	\
		my_strcpy.c	\
		my_strdup.c	\
		my_str_isalpha.c	\
		my_str_islower.c	\
		my_str_isnum.c	\
		my_str_isprintable.c	\
		my_str_isupper.c	\
		my_strlen.c	\
		my_strlowcase.c	\
		my_strncat.c	\
		my_strncmp.c	\
		my_strncpy.c	\
		my_strstr.c	\
		my_strupcase.c	\
		my_swap.c	\
		my_put_unsigned_nbr.c	\
		my_put_float.c	\
		my_flag_x.c	\
		my_flag_up_x.c	\
		my_flag_p.c	\
		my_flag_e.c	\
		my_put_octal.c	\
		my_isneg_printf.c	\
		my_atoi.c	\
		put_error.c	\
		trailing_spaces.c	\
		my_str_to_word_array.c	\
		my_nbr_str.c	\
		my_printf.c	\
		printf_char.c	\
		printf_decimal.c	\
		printf_float.c	\
		printf_hex.c	\
		printf_hex_up_x.c	\
		printf_intoctal.c	\
		printf_modulo.c	\
		printf_pointer.c	\
		printf_scientific.c	\
		printf_sign_plus.c	\
		printf_string.c	\
		printf_unsdecimal.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):        $(OBJ)
	ar rc $(NAME) *.o $(OBJ)
	cp libmy.a ../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

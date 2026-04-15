##
## EPITECH PROJECT, 2025
## my_radar
## File description:
## Makefile
##

SRC	=	src/my_sh.c	\
		src/builtins/cd.c	\
		src/builtins/setenv.c	\
		src/builtins/unsetenv.c	\
		src/execution/exec.c	\
		src/execution/pipe.c	\
		src/parsing/detect.c	\
		src/parsing/readline.c	\
		src/utils/oldpwd.c	\
		src/utils/path.c	\
		src/builtins/exit.c	\
		src/builtins/demo.c	\
		src/execution/semicolone.c

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

LIB 	=	lib/my/libmy.a

CC	=	epiclang

CFLAGS	+=	-I./include -I./lib/my

LDFLAGS	=	-L./lib -lmy

all: $(NAME)

$(LIB):
	make -C lib/my

$(NAME):	$(LIB) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)
	make clean -C lib/my

fclean:	clean
	make fclean -C lib/my
	rm -f lib/libmy.a
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
.NOPARALLEL: re

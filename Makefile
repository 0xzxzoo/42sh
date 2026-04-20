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
		src/builtins/where.c	\
		src/builtins/which.c	\
		src/execution/exec.c	\
		src/execution/exec_redir.c	\
		src/parsing/detect.c	\
		src/parsing/readline.c	\
		src/parsing/ast_nodes.c	\
		src/parsing/exec_ast.c	\
		src/parsing/exec_nodes.c	\
		src/parsing/parser_cmd.c	\
		src/parsing/parser_core.c 	\
		src/parsing/parser_utils.c	\
		src/parsing/parser_redir.c	\
		src/parsing/word_array.c \
		src/utils/oldpwd.c	\
		src/utils/path.c	\
		src/builtins/exit.c	\
		src/builtins/demo.c

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

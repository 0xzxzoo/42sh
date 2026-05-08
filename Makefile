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
		src/builtins/jobs.c	\
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
		src/parsing/globbing.c \
		src/parsing/variables.c \
		src/parsing/backtick/backtick_exec.c \
		src/parsing/backtick/backtick_extract.c \
		src/parsing/backtick/backtick_find.c \
		src/parsing/backtick/backtick_replace.c \
		src/parsing/backtick/backtick_expand.c \
		src/jobs/job_utils.c	\
		src/jobs/job_launch.c 	\
		src/jobs/job_list.c 	\
		src/jobs/job_parser.c 	\
		src/jobs/job_wait.c	\
		src/utils/oldpwd.c	\
		src/utils/path.c	\
		src/builtins/exit.c	\
		src/builtins/fg.c	\
		src/builtins/bg.c	\
		src/builtins/demo.c	\
		src/builtins/history.c	\
		src/utils/env.c	

OBJ	=	$(SRC:.c=.o)

NAME	=	42sh

SRC_NO_MAIN =   $(filter-out src/my_sh.c, $(SRC))

LIB 	=	lib/my/libmy.a

CC	=	epiclang

CFLAGS	+=	-I./include -I./lib/my

LDFLAGS	=	-L./lib -lmy

all: $(NAME)

$(LIB):
	make -C lib/my

$(NAME):	$(LIB) $(OBJ)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) $(LDFLAGS)

tests_run: fclean $(LIB)
	$(CC) -o unit_tests $(SRC_NO_MAIN) tests/test_builtins.c 	tests/test_utils.c \
	tests/parsing/test_parser.c	tests/parsing/test_exec.c tests/parsing/test_parsing_utils.c \
	tests/parsing/test_word_array.c tests/parsing/test_backstick.c tests/test_backtick_exec.c \
	tests/test_where_which.c \
		$(CFLAGS) $(LDFLAGS) --coverage -lcriterion
	./unit_tests
	gcovr . --root . --exclude tests/ --gcov-executable "llvm-cov gcov" --txt-metric branch --print-summary

clean:
	rm -f $(OBJ)
	make clean -C lib/my

fclean:	clean
	make fclean -C lib/my
	rm -f lib/libmy.a
	rm -f $(NAME)
	rm -f unit_tests
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete
	find . -name "unit_tests-*.gcda" -delete

re:	fclean all

.PHONY:	all clean fclean re tests_run
.NOTPARALLEL: re

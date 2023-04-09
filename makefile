SRCS =	ast/ast.c \
		execute/execute.c  \
		execute/pipe.c \
		execute/redirections.c\
		execute/heredoc.c\
		execute/subshell.c \
		execute/execute_imp.c \
		execute/checker.c \
		execute/mix.c \
		execute/rand_tmp.c\
		main.c	\
		commands/cd.c \
		commands/echo.c \
		commands/env.c \
		commands/export.c \
		commands/pwd.c \
		commands/unset.c \
		env/env.c		\
		env/lst2env.c	\


NAME = minishell


OBJS = $(SRCS:.c=.o)

MH = execute/exectue.h ast/ast.h commands/commands.h env/env.h minishell.h libft.h

CC_FLAGS = 

all: $(NAME)

$(NAME): $(OBJS)
	cc $(OBJS) libft.a -o $(NAME) -L$(shell brew --prefix readline)/lib -lreadline

%.o : %.c $(MH)
	cc  -I$(shell brew --prefix readline)/include -c $< -o $@ -I minishell.h


	

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY : clean fclean re all

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
		commands/sort_env.c \
		env/env.c		\
		env/lst2env.c	\


NAME = minishell


OBJS = $(SRCS:.c=.o)

MH = execute/exectue.h ast/ast.h commands/commands.h env/env.h minishell.h libft.h

CC_FLAGS = 

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cc  $(OBJS) libft.a -L$(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	@echo "minishell created"


%.o:%.c 
	@echo "Building $@..."
	@$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@ -I ./minishell.h
	@echo "Done building $@!"

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY : clean fclean re all

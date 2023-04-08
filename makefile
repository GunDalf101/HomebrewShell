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
		gnl/get_next_line_utils.c \
		gnl/get_next_line.c


NAME = minishell


OBJS = $(SRCS:.c=.o)

MH = execute/exectue.h ast/ast.h commands/commands.h env/env.h minishell.h libft.h

CC_FLAGS = -lreadline#-Wall -Wextra -Werror

all: $(NAME)


%.o : %.c $(MH)
	cc $(CC_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(OBJS) libft.a -o $(NAME) -lreadline

	

clean:
	rm -f $(OBJS) $(OBJSB)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY : clean fclean re all

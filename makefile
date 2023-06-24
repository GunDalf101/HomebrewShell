NAME = minishell

SOURCES = exec/env/env.c \
		exec/env/lst2env.c	\
		exec/env/clearenv.c \
		parsing_realm/ast/ast.c \
		parsing_realm/ast/astV2.c \
		parsing_realm/ast/clearast.c\
		parsing_realm/ast/mini_tree.c \
		parsing_realm/ast/red_lister.c \
		parsing_realm/lexical_analyzer/lexer.c \
		parsing_realm/lexical_analyzer/tokens_gen.c \
		parsing_realm/lexical_analyzer/split_with_a_twist.c \
		parsing_realm/lexical_analyzer/input_syntax_analysis.c \
		parsing_realm/lexical_analyzer/tokens_syntax_analysis.c \
		parsing_realm/lexical_analyzer/tokens_syntax_analysis_extended.c \
		parsing_realm/lexical_analyzer/paren_quotes.c \
		parsing_realm/lexical_analyzer/space_expansion.c \
		parsing_realm/lexical_analyzer/redir_parser.c\
		parsing_realm/lexical_analyzer/command_parser.c \
		parsing_realm/lexical_analyzer/len_counter.c \
		parsing_realm/ast/ast_maker.c \
		parsing_realm/parsing101.c\
		exec/execute/execute.c  \
		exec/execute/pipe.c \
		exec/execute/wild_command.c \
		exec/execute/wild_counter.c \
		exec/execute/redirections.c\
		exec/execute/finder.c \
		exec/execute/heredoc.c\
		exec/execute/heredoc_utils.c\
		exec/execute/subshell.c \
		exec/execute/execute_imp.c \
		exec/execute/checker.c \
		exec/execute/mix.c \
		exec/execute/rand_tmp.c\
		exec/execute/expand.c \
		exec/execute/exit.c \
		exec/execute/heredoc_expansion.c \
		exec/execute/heredoc_first.c \
		exec/execute/heredoc_read.c \
		exec/execute/waiting_status.c \
		exec/execute/wild_for_red.c	\
		exec/execute/fds_dupping.c \
		exec/commands/cd.c \
		exec/commands/echo.c \
		exec/commands/env.c \
		exec/commands/export.c \
		exec/commands/pwd.c \
		exec/commands/unset.c \
		exec/commands/sort_env.c \
		exec/commands/export_init.c	\
		minishell.c \


OBJECTS = $(SOURCES:.c=.o)

INCLUDES = minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

all: libft $(NAME) 
	@if [ $$? -eq 0 ]; then \
		echo "\033[3m\033[1m\033[42m\033[31m~~Nothing to be done for 'all' anymore~~\033[0m"; \
	fi



$(NAME):$(OBJECTS) $(GNLOBJ) 
	@cc  $(OBJECTS) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	@echo "\033[47m\033[30m\033[1m           \`$@ linked\`           \033[0m"

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -I$(shell brew --prefix readline)/include -c $< -o $@
	@echo "\033[33m$< compiled \033[0m"

libft:
	@echo '                                             _______________________'
	@echo '   _______________________-------------------                        \'
	@echo ' /:--__                                                              |'
	@echo '||< > |                                   ___________________________/'
	@echo '| \__/_________________-------------------                         |'
	@echo '|                                                                  |'
	@echo ' |                  THE SCROLL OF INFINITE WISDOM                   |'
	@echo ' |                                                                  |'
	@echo ' |       Three Rings for the Elven-kings under the sky,             |'
	@echo '  |        Seven for the Dwarf-lords in their halls of stone,        |'
	@echo '  |      Nine for Mortal Men doomed to die,                          |'
	@echo '  |        One for the Dark Lord on his dark throne                  |'
	@echo '  |      In the Land of Mordor where the Shadows lie.                 |'
	@echo '   |       One Ring to rule them all, One Ring to find them,          |'
	@echo '   |       One Ring to bring them all and in the darkness bind them   |'
	@echo '   |     In the Land of Mordor where the Shadows lie.                |'
	@echo '  |                                                                  |'
	@echo '  |                                       -----------------          |'
	@echo '  |                                     ))SnooZe && GunDalf ((       |'
	@echo '  |                                       -----------------          |'
	@echo '  |                                              ____________________|_'
	@echo '  |  ___________________-------------------------                       \'
	@echo '  |/ --_                                                                 |'
	@echo '  ||[ ]||                                            ___________________/'
	@echo '   \===/___________________--------------------------'
	@echo ''
	@make -s -C libft bonus
	@echo "\033[35m$@ have been made \033[0m"

clean:
	@rm -f $(OBJECTS)
	@make -s -C libft clean
	@echo "\033[3m\033[1m\033[42m\033[31m~~   The objects have been cleaned   ~~\033[0m"; \
	
fclean: clean
	@make -s -C libft fclean
	@rm -f minishell
	@echo "\033[3m\033[1m\033[42m\033[31m~~The directory have been fully wiped~~\033[0m"; \

re: fclean all

.PHONY: all bonus libft clean fclean re
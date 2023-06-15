
#-------------------COLORS------------------#
DEF = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
RED = \033[31;2m
BLACK = \033[38;5;238m
BLUE = \033[38;5;153m
GREEN = \033[38;5;48m
YELLOW = \033[38;5;226m
ORANGE = \033[38;5;202m
PINK = \033[38;5;198m
PURPLE = \033[38;5;147m
UP = UP = \033[A

#-------------------SRCS--------------------#
SRCS	=	main.c \
			get_vars.c \
			minishell_utils.c \
			history.c \
			lst_functions.c \
			get_token.c \
			check_token.c \
			handle_quotes.c \
			get_token_type.c

OBJS = $(SRCS:.c=.o)

#------------------COMPILE------------------#
CC = gcc
CFLAGS = -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS += -fsanitize=address -g3
endif

.c.o:
	@$(CC) $(CFLAGS) -c -I ./inc/ $< -o $(<:.c=.o)

#------------------RULES---------------------#
NAME = minishell

all : $(NAME)

$(NAME): $(OBJS)
	@echo ""
	@echo "	$(BOLD)$(PINK)$(UNDERLINE)Compiling...$(DEF)  $(PURPLE)$(BOLD)Minishell$(DEF) ⏳"
	@$(MAKE) -C ./libft/
	@$(CC) $(CFLAGS) $(OBJS) -lreadline ./libft/libft.a -o $(NAME)
	@clear
	@echo "	$(YELLOW)$(BOLD)Compiled ! ✨$(DEF)"

debug: fclean
	@$(MAKE) DEBUG=1

clean:
	@$(MAKE) clean -C ./libft/
	@rm -rf $(OBJS)
	@echo "	❌ $(BOLD)$(RED)Deleted file .o$(DEF)"

fclean: clean
	@rm -rf ./libft/libft.a
	@rm -rf $(NAME)
	@echo "	❌ $(BOLD)$(RED)Deleted file .a$(DEF)"

re: fclean all

.PHONY: all clean fclean re debug
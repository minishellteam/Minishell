SRCS	=	main.c \
			get_vars.c \
			minishell_utils.c

OBJS = $(SRCS:.c=.o)

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

CC = gcc
CFLAGS = -Wall -Werror -Wextra
ifdef DEBUG
CFLAGS += -fsanitize=address -g3
endif

.c.o:
	@$(CC) $(CFLAGS) -c -I ./inc/ $< -o $(<:.c=.o)

NAME = minishell

all : $(NAME)

$(NAME): $(OBJS)
	@echo "	$(PURPLE)$(UNDERLINE)Compiling...\033[0m ⏳"
	@$(MAKE) -C ./libft/
	@$(CC) $(CFLAGS) $(OBJS) -lreadline ./libft/libft.a -o $(NAME)
	@clear
	@echo "	$(YELLOW)$(BOLD)Compiled ! ✨\033[0m"

debug:
	@$(MAKE) DEBUG=1

clean:
	@$(MAKE) clean -C ./libft/
	@rm -rf $(OBJS)
	@echo "	$(RED)Deleted file .o \033[0m"

fclean: clean
	@rm -rf ./libft/libft.a
	@rm -rf $(NAME)
	@echo "	$(RED)Deleted file .a\033[0m"

re: fclean all

.PHONY: all clean fclean re debug
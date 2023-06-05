# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkerkeni <mkerkeni@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 12:55:09 by mkerkeni          #+#    #+#              #
#    Updated: 2023/05/19 09:45:13 by mkerkeni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = Libft/
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g3

SRCS =  mand_part/pipex.c \
		mand_part/execution.c \

SRCS_BONUS = bonus_part/pipex_bonus.c \
			 bonus_part/process_bonus.c \
			 bonus_part/create_first_process.c \
			 bonus_part/execution_bonus.c \

OBJS_MAND = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifndef BONUS
OBJS = $(OBJS_MAND)
else
OBJS = $(OBJS_BONUS)
endif

%.o:%.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "	Compilation in progress..."
	@$(MAKE) -C $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $^ $(LIBFT)libft.a
	@echo "	Compiled !"

bonus:
	@$(MAKE) BONUS=1
	
clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@rm -f Libft/libft.a

re: fclean all

.PHONY: all clean fclean re bonus

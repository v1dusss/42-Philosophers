# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 23:51:06 by vsivanat          #+#    #+#              #
#    Updated: 2024/07/17 23:51:09 by vsivanat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -g
OBJDIR := obj

VPATH = \
		includes \
		src

SRC = main.c \
		philo.c \
		parsing.c \
		dinner.c \
		utils.c \
		get_variables.c \
		get_variables_2.c

OBJ	:=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "\033[1;32m ✅ [philo created]\033[0m"

clean:
	@rm -rf $(OBJDIR)

fclean:
	@echo "\033[1;33m 🗑️  Deleting the obj directory and executable... 🗑️\033[0m"
	@make clean
	@rm -f $(NAME)
	@echo "\033[0;37m 🧹 [philo deleted]\033[0m"

re: fclean all

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

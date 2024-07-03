# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 19:20:48 by babonnet          #+#    #+#              #
#    Updated: 2024/04/23 18:37:06 by babonnet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread -MMD -MP -g
SRC_DIR = ./
OBJ_DIR = obj
HSRCS = include
LIBFT = libft/libft.a
SRC = $(shell find . -name '*.c')
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(notdir $<)...$(NC)"
	@$(CC) $(CFLAGS) -I $(HSRCS) -o $@ -c $<

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean lclean
	@if [ -f $(NAME) ]; then \
		echo "$(RED)Cleaning executable $(NAME)...$(NC)"; \
		rm -f $(NAME); \
		fi

re : fclean all

.PHONY: all clean fclean lclean re bonus

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPULE = \e[0;35m
NC = \033[0m

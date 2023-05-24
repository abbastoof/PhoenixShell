# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:54:55 by atoof             #+#    #+#              #
#    Updated: 2023/05/24 13:48:43 by atoof            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = src/
BUILT_IN_DIR = src/built-in/
SRC = main.c helper.c ft_strcmp.c commands.c ft_realloc.c
SRC_BUILT = cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(BUILT_IN_DIR), $(SRC_BUILT))
HEADER_DIR = header/
HEADER = minishell.h
OBJ_DIR = obj/
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a
FLAGS = -Wall -Werror -Wextra

# ANSI escape sequences for text formatting
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m

vpath %.c $(SRC_DIR) $(BUILT_IN_DIR)
vpath %.h $(HEADER_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@if [ -f $(NAME) ] && [ "$(OBJS)" -ot "$(NAME)" ]; then \
		echo "$(GREEN)$(BOLD)$(NAME) is already up-to-date!$(NC)"; \
	else \
		echo "$(YELLOW)$(BOLD)Compiling $(NAME)...$(NC)"; \
		make -C ./libft; \
		cc $(FLAGS) -lreadline $(OBJS) -I$(HEADER_DIR) $(LIBFT) -o $@ ; \
		echo "$(GREEN)$(BOLD)$(NAME) successfully compiled!$(NC)"; \
	fi

$(OBJ_DIR)%.o: %.c $(HEADER_DIR)$(HEADER)
	@echo "$(YELLOW)$(BOLD)Compiling $<...$(NC)"
	@mkdir -p $(@D)
	@cc $(FLAGS) -I$(HEADER_DIR) -c -o $@ $<

clean:
	@echo "$(CYAN)$(BOLD)Cleaning object files...$(NC)"
	@make clean -C ./libft
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(CYAN)$(BOLD)Cleaning $(NAME)...$(NC)"
	@make fclean -C ./libft
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) successfully cleaned!$(NC)"

re: fclean all


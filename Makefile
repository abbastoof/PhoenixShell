# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 12:54:55 by atoof             #+#    #+#              #
#    Updated: 2023/08/23 16:42:02 by mtoof            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_DIR = src/
BUILT_IN_DIR = src/built-in/
LEXER_D = src/lexer/
UTILS_D = src/utils/
TREE_D = src/tree/
EXEC_D = src/exec/
ENV_D = src/env/
SRC_UTILS = ft_realloc.c ft_strcmp.c ft_strnjoin.c ft_atol.c free_double_ptr.c \
			ft_listsize.c
SRC = main.c signals.c heredoc_signals.c
SRC_BUILT = cd.c echo.c env.c exit.c export.c pwd.c unset.c export_helper.c cd_utils.c
SRC_LEX = lexer.c expand_var.c var_finder.c dollar_sign.c ft_free.c split_line.c \
			split_utils.c split_utils2.c token_utils.c expand_quotes.c syntax.c \
			check_quotes.c check_for_heredoc.c syntax_utils.c
SRC_TREE = create_tree.c utils.c free_tree.c parse_cmd_node.c parse_redir_node.c \
			parse_args_list.c
SRC_EXEC = child.c create_pipe.c error.c exec_tree.c exec_redir.c exec_cmd.c exec_cmd_utils.c \
			heredoc.c open_files.c
SRC_ENV = env_init.c env_utils.c env_utils2.c
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(BUILT_IN_DIR), $(SRC_BUILT)) \
		$(addprefix $(LEXER_D), $(SRC_LEX)) $(addprefix $(UTILS_D), $(SRC_UTILS)) \
		$(addprefix $(TREE_D), $(SRC_TREE)) $(addprefix $(EXEC_D), $(SRC_EXEC)) \
		$(addprefix $(ENV_D), $(SRC_ENV))
HEADER_DIR = header/
HEADER = minishell.h
OBJ_DIR = obj/
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
LIBFT = ./libft/libft.a
FLAGS = -Wall -Werror -Wextra
ERROR_FLAGS =  -fsanitize=address -static-libsan -g -fno-omit-frame-pointer -overflow
EXTRA_FLAGS = -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

# ANSI escape sequences for text formatting
BOLD = \033[1m
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[0;36m
NC = \033[0m

vpath %.c $(SRC_DIR) $(BUILT_IN_DIR) $(LEXER_D) $(UTILS_D)
vpath %.h $(HEADER_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@if [ -f $(NAME) ] && [ "$(OBJS)" -ot "$(NAME)" ]; then \
		echo "$(GREEN)$(BOLD)$(NAME) is already up-to-date!$(NC)"; \
	else \
		echo "$(YELLOW)$(BOLD)Compiling $(NAME)...$(NC)"; \
		make -C ./libft; \
		cc $(FLAGS) $(EXTRA_FLAGS) $(OBJS) -I$(HEADER_DIR) $(LIBFT) -o $@ ; \
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


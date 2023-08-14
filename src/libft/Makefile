# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 13:20:08 by atoof             #+#    #+#              #
#    Updated: 2023/03/06 12:10:20 by atoof            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h
FLAG = -Wall -Wextra -Werror
OBJ_DIR = obj

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_convert_number.c ft_isalnum.c \
      ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c\
      ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c ft_putchar.c \
      ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
      ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
      ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
      ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c

SRC_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
        ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
        ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c get_next_line_bonus.c

OBJS = $(SRC:.c=.o)
OBJS_B = $(SRC_B:.c=.o)

all: $(NAME)
	@echo "\033[1;32m[✔] Successfully compiled libft.a!\033[0m"

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJS))
	@ar rcs $(NAME) $(addprefix $(OBJ_DIR)/, $(OBJS))
	@echo "\033[1;34m[✨] Creating libft.a...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@cc $(FLAG) -c $< -o $@

bonus: $(addprefix $(OBJ_DIR)/, $(OBJS_B))
	@echo "\033[1;33m[⭐] Compiling bonus functions...\033[0m"
	@ar rcs $(NAME) $(addprefix $(OBJ_DIR)/, $(OBJS_B))

$(addprefix $(OBJ_DIR)/, $(OBJS_B)): $(SRC_B)
	@mkdir -p $(OBJ_DIR)
	@cc $(FLAG) -c $(SRC_B) -I $(HEADER)
	@mv $(OBJS_B) $(OBJ_DIR)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@echo "\033[1;35m[🧹] Cleaning object files...\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "\033[1;35m[🧹] Cleaning libft.a...\033[0m"

re: fclean all

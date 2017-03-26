# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 11:07:10 by lbopp             #+#    #+#              #
#    Updated: 2017/03/26 16:46:58 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/
CLANG = clang
SRC_NAME = main.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
RM = rm -f

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[32m=== Compilation of libft\t\t\tDONE"
	@make -C libft
	$(CLANG) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -I libft/includes -lft -L libft -ltermcap
	@echo "\033[32m=== Compilation\t[DONE]"

%.o: %.c
	@echo "\033[36m=Compilation of $^"
	$(CLANG) $(CFLAGS) -c $^ -o $@ -I includes -I libft/includes

clean:
	@make -C libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all

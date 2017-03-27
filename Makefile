# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 11:07:10 by lbopp             #+#    #+#              #
#    Updated: 2017/03/27 13:10:52 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/
CLANG = clang
SRC_NAME = lexer.c\
		   main.c
SRC_TEST = src/lexer.c\
		   src/maintest.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
OBJ_TEST = $(SRC_TEST:.c=.o)
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

test:
	@echo "\033[32m=== Compilation of libft\t\t\tDONE"
	@make -C libft
	$(CLANG) $(CFLAGS) -o 21sh $(SRC_TEST) -I includes -I libft/includes -lft -L libft
	@echo "\033[32m=== Compilation\t[DONE]"

clean:
	@make -C libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all

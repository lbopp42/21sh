# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 11:07:10 by lbopp             #+#    #+#              #
#    Updated: 2017/04/02 16:43:47 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/
CLANG = clang
SRC_NAME = find_type.c\
		   isop.c\
		   isquote.c\
		   get_last_state.c\
		   get_last_token.c\
		   lexer.c\
		   main.c\
		   print_debug.c\
		   state_management.c\
		   token_management.c
SRC_TEST = src/find_type.c\
		   src/isop.c\
		   src/isquote.c\
		   src/get_last_state.c\
		   src/get_last_token.c\
		   src/lexer.c\
		   src/maintest.c\
		   src/print_debug.c\
		   src/state_management.c\
		   src/token_management.c
SRC_PATH = src
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(SRC:.c=.o)
OBJ_TEST = $(SRC_TEST:.c=.o)
RM = rm -f

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "\033[32m=== Compilation of libft\t[DONE]\033[0m"
	$(CLANG) $(CFLAGS) -o $(NAME) $(OBJ) -I includes -I libft/includes -lft -L libft -ltermcap
	@echo "\033[32m=== Compilation\t[DONE]\033[0m"

%.o: %.c
	@echo "\033[36m=Compilation of $^"
	$(CLANG) $(CFLAGS) -c $^ -o $@ -I includes -I libft/includes

test:
	@make -C libft
	@echo "\033[32m=== Compilation of libft\t[DONE]\033[0m"
	@$(CLANG) $(CFLAGS) -o 21sh $(SRC_TEST) -I includes -I libft/includes -lft -L libft
	@echo "\033[32m=== Compilation\t[DONE]\033[0m" && ./21sh

clean:
	@make -C libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all

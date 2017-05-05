# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 11:07:10 by lbopp             #+#    #+#              #
#    Updated: 2017/05/05 13:42:19 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CFLAGS = -Wall -Werror -Wextra -g
LIBFT = libft/
CLANG = clang
LEXER_SRC = find_type.c\
			isop.c\
			isquote.c\
			get_last_state.c\
			get_last_token.c\
			lexer.c\
			print_debug.c\
			state_management.c\
			token_management.c

SRC_NAME = main.c
SRC_TEST = src/lexer/lexer.c\
		   src/lexer/add_to_current_token.c\
		   src/lexer/create_new_token.c\
		   src/lexer/is_digit_token.c\
		   src/lexer/management_of_op.c\
		   src/lexer/state_management.c\
		   src/parser/parser.c\
		   lsh_test/launch_tests.c\
		   lsh_test/test_lexer1.c\
		   lsh_test/test_lexer2.c\
		   lsh_test/test_lexer3.c\
		   lsh_test/test_lexer4.c\
		   lsh_test/test_lexer5.c\
		   lsh_test/test_lexer6.c\
		   lsh_test/test_lexer7.c\
		   lsh_test/test_lexer8.c\
		   lsh_test/test_lexer9.c\
		   lsh_test/test_lexer10.c\
		   lsh_test/test_parser1.c\
		   lsh_test/test_parser2.c\
		   lsh_test/test_parser3.c\
		   lsh_test/test_parser4.c\
		   lsh_test/test_parser5.c\
		   lsh_test/test_parser6.c\
		   lsh_test/test_parser7.c\
		   lsh_test/test_parser8.c\
		   lsh_test/test_parser9.c\
		   lsh_test/test_parser10.c
SRC_PATH = src
LEXER_PATH = src/lexer
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
LEXER = $(addprefix $(LEXER_PATH)/,$(LEXER_SRC))
OBJ = $(SRC:.c=.o)\
	$(LEXER:.c=.o)
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
	@$(CLANG) $(CFLAGS) -o test_lsh $(SRC_TEST) -I includes -I libft/includes -lft -L libft
	@echo "\033[32m=== Compilation\t[DONE]\033[0m" && ./test_lsh

clean:
	@make -C libft clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all

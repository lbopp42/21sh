# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbopp <lbopp@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/02 11:07:10 by lbopp             #+#    #+#              #
#    Updated: 2017/09/14 14:11:14 by lbopp            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
CFLAGS = -g
LIBFT = libft/
CLANG = gcc
LEXER_SRC = add_to_current_token.c\
			create_new_token.c\
			is_digit_token.c\
			is_piece_of_bigop.c\
			lexer.c\
			management_of_op.c\
			state_management.c\
			treatment_newline.c\
			treatment_of_quote.c\
			treatment_of_word.c
PARSER_SRC = list_to_array.c\
			 parser.c
EXPAND_SRC = main_expand.c
EXECUTION_SRC = execution.c
BUILTINS_SRC = array_to_list.c\
			   ft_cd.c\
			   ft_echo.c\
			   ft_env.c\
			   ft_exit.c\
			   ft_setenv.c\
			   ft_unsetenv.c\
			   list_to_tab.c\
			   tab_to_list.c
SRC_NAME = main.c

SRC_TEST = src/lexer/lexer.c\
		   src/lexer/add_to_current_token.c\
		   src/lexer/create_new_token.c\
		   src/lexer/is_digit_token.c\
		   src/lexer/is_piece_of_bigop.c\
		   src/lexer/management_of_op.c\
		   src/lexer/state_management.c\
		   src/lexer/treatment_of_quote.c\
		   src/lexer/treatment_of_word.c\
		   src/lexer/treatment_newline.c\
		   src/parser/parser_AST.c\
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
		   lsh_test/test_lexer11.c\
		   lsh_test/test_lexer12.c\
		   lsh_test/test_lexer13.c\
		   lsh_test/test_lexer14.c\
		   lsh_test/test_lexer15.c\
		   lsh_test/test_lexer16.c\
		   lsh_test/test_parser1.c\
		   lsh_test/test_parser2.c\
		   lsh_test/test_parser3.c\
		   lsh_test/test_parser4.c\
		   lsh_test/test_parser5.c\
		   lsh_test/test_parser6.c\
		   lsh_test/test_parser7.c\
		   lsh_test/test_parser8.c\
		   lsh_test/test_parser9.c\
		   lsh_test/test_parser10.c\
		   lsh_test/test_parser11.c\
		   lsh_test/test_parser12.c\
		   lsh_test/test_parser13.c\
		   lsh_test/test_parser14.c\
		   lsh_test/test_parser15.c\
		   lsh_test/test_parser16.c
SRC_PATH = src
LEXER_PATH = src/lexer
PARSER_PATH = src/parser
EXPAND_PATH = src/expand
EXECUTION_PATH = src/execution
BUILTINS_PATH = src/builtins
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
LEXER = $(addprefix $(LEXER_PATH)/,$(LEXER_SRC))
PARSER = $(addprefix $(PARSER_PATH)/,$(PARSER_SRC))
EXPAND = $(addprefix $(EXPAND_PATH)/,$(EXPAND_SRC))
EXECUTION = $(addprefix $(EXECUTION_PATH)/,$(EXECUTION_SRC))
BUILTINS = $(addprefix $(BUILTINS_PATH)/,$(BUILTINS_SRC))
OBJ = $(SRC:.c=.o)\
	$(LEXER:.c=.o)\
	$(PARSER:.c=.o)\
	$(EXPAND:.c=.o)\
	$(EXECUTION:.c=.o)\
	$(BUILTINS:.c=.o)
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

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/07 13:02:54 by bduron            #+#    #+#              #
#    Updated: 2017/02/08 16:56:29 by bduron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER= checker
PS= push_swap

CC= gcc
CFLAGS= -Wall -Wextra -Werror
LIBFT= -Llibft -lft 

MKDIR= mkdir -p
RM= rm -rf

INC_DIR= includes/

SHARED_SRC= command_launcher.c \
			error_handling.c \
			sort_commands.c \
			stack_management.c \
			stack_print.c
PS_SRC= 	algo_inits.c \
			algo_quartile.c \
			algo_small.c \
			algo_utils.c \
			push_swap.c \
			quicksort.c \
			stack_state.c
CHECKER_SRC= checker.c \
			checker_display.c \
			checker_parsing.c	

SHARED_OBJ= $(SHARED_SRC:.c=.o)
PS_OBJ= $(PS_SRC:.c=.o)
CHECKER_OBJ= $(CHECKER_SRC:.c=.o)

VPATH= srcs/checker/:srcs/shared/:srcs/push_swap/

########################
#    Makefile rules    # 
########################

all: libft $(CHECKER) $(PS)

libft:
	@make -C libft

# Executables 

$(CHECKER): $(CHECKER_OBJ) $(SHARED_OBJ) 
	@$(CC) -o $@ $(CFLAGS) $^ -I $(INC_DIR) $(LIBFT) 
	@echo "Compiling [$@]"

$(PS): $(PS_OBJ) $(SHARED_OBJ) 
	@$(CC) -o $@ $(CFLAGS) $^ -I $(INC_DIR) $(LIBFT) 
	@echo "Compiling [$@]"

# Object files 

$(CHECKER_OBJ): $(CHECKER_SRC)
	@$(CC) -c $^ $(CFLAGS) -I $(INC_DIR) 	
	@echo "Compiling [$^]"

$(SHARED_OBJ): $(SHARED_SRC)
	@$(CC) -c $^ $(CFLAGS) -I $(INC_DIR) 
	@echo "Compiling [$^]"

$(PS_OBJ): $(PS_SRC)
	@$(CC) -c $^ $(CFLAGS) -I $(INC_DIR) 
	@echo "Compiling [$^]"

# Cleaning rules 

clean:
	@rm -f $(PS_OBJ) $(SHARED_OBJ) $(CHECKER_OBJ)
	@echo "Cleaning [$(PS_OBJ) $(SHARED_OBJ) $(CHECKER_OBJ)]"	

fclean: clean
	@rm -rf $(CHECKER) $(PS)
	@make fclean -C libft
	@echo "Cleaning [libft checker push_swap]"	

re: fclean all

.PHONY: clean fclean re libft 

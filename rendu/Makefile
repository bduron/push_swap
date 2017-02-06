# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bduron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/06 14:17:35 by bduron            #+#    #+#              #
#*   Updated: 2016/12/27 15:23:15 by bduron           ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

CHECKER= checker
PS= push_swap
SHARED_SRC= srcs/shared/*.c
PS_SRC= srcs/push_swap/*.c
CHECKER_SRC= srcs/checker/*.c
OBJ= *.o
HEADER= -I includes
FLAGS= -g -Wall -Wextra -Werror ##-fsanitize=address
LIBFT= -Llibft -lft 

all: $(CHECKER) 

$(CHECKER): check ps
	@echo "Compiling checker & push_swap... OK"

check:
	@make -C libft
	@gcc -o $(CHECKER) $(FLAGS) $(SHARED_SRC) $(CHECKER_SRC) $(LIBFT) $(HEADER)
	@echo "Compiling checker... OK"

ps:
	@make -C libft
	@gcc -o $(PS) $(FLAGS) $(SHARED_SRC) $(PS_SRC) $(LIBFT) $(HEADER)
	@echo "Compiling push_swap... OK"

clean:
#	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(CHECKER) $(PS) checker.dSYM push_swap.dSYM
	@make fclean -C libft
	@echo "Cleaning..."	

re: fclean all
 

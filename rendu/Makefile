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
HEADER= -I includes -I libft/includes
FLAGS= -g -Wall -Wextra -Werror ##-fsanitize=address
 

all: $(CHECKER)

$(CHECKER):
	@make -C libft
	@gcc -o $(CHECKER) $(FLAGS) -L libft -lft $(SRC) $(HEADER)
	@echo "Compiling checker... OK"

check:
	@make -C libft
	@gcc -o $(CHECKER) $(FLAGS) $(SHARED_SRC) $(CHECKER_SRC) -Llibft -lft -I includes
	@echo "Compiling checker... OK"

ps:
	@make -C libft
	@gcc -o $(PS) $(FLAGS) $(SHARED_SRC) $(PS_SRC) -Llibft -lft -I includes
	@echo "Compiling push_swap... OK"

clean:
#	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(CHECKER) $(PS) checker.dSYM
	@make fclean -C libft
	@echo "Cleaning..."	

re: fclean all
 

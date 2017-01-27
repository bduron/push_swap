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

NAME= checker
PS= push_swap
SRC= srcs/*.c
OBJ= *.o
HEADER= -I includes -I libft/includes
FLAGS= -g -Wall -Wextra -Werror
 

all: $(NAME)

$(NAME):
	@make -C libft
	@gcc -o $(NAME) $(FLAGS) -L libft -lft $(SRC) $(HEADER)
	@echo "Compiling checker... OK"

linux:
	@make -C libft
	@gcc -o $(NAME) $(FLAGS) $(SRC) -Llibft -lft -I includes
	@echo "Compiling checker... OK"

ps:
	@make -C libft
	@gcc -o $(PS) $(FLAGS) $(SRC) -Llibft -lft -I includes
	@echo "Compiling push_swap... OK"

clean:
#	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(PS) checker.dSYM
	@make fclean -C libft
	@echo "Cleaning..."	

re: fclean all

rl: fclean linux 

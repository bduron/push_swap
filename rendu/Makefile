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
OBJ= $(SHARED_SRC:.c=.o) $(PS_SRC:.c=.o) $(CHECKER_SRC:.c=.o) 
HEADER= -I includes
FLAGS= -Wall -Wextra -Werror
LIBFT= -Llibft -lft 

all: $(CHECKER) 

$(CHECKER): lib check ps
	@echo "Compiling checker & push_swap... OK"

lib: 	
	@make -C libft

check:
	@gcc -o $(CHECKER) $(FLAGS) $(SHARED_SRC) $(CHECKER_SRC) $(LIBFT) $(HEADER)
	@echo "Compiling checker... OK"

ps:
	@gcc -o $(PS) $(FLAGS) $(SHARED_SRC) $(PS_SRC) $(LIBFT) $(HEADER)
	@echo "Compiling push_swap... OK"

clean:
#	@rm -f $(OBJ)

fclean: clean
	@rm -rf $(CHECKER) $(PS)
	@make fclean -C libft
	@echo "Cleaning..."	

re: fclean all
 

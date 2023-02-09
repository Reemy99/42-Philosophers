# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: realdahh <realdahh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/10 19:24:46 by realdahh          #+#    #+#              #
#    Updated: 2023/02/05 22:35:52 by realdahh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CFILES	= 	main.c\
			check.c\
			eating.c\
			error.c\
			libft.c\
			parsing.c\
			philo.c\
			routine.c\
			utils.c
			
HEADERS 	= ./philo.h

OBJECTS 		= $(CFILES:.c=.o)

CFLAGS 		= -Wall -Wextra -Werror

CC 			= gcc

RED			= \033[1;31m
BLUE 		= \033[1;34m
GREEN		= \033[1;32m
No_COLOR	= \033[0m

all: 		$(NAME)
$(NAME): 	$(OBJECTS)

	@$(CC) -pthread -g $(CFILES) $(CFLAGS) -o philo
	@echo "$(GREEN) OK philo CREATED$(No_COLOR)"
	@echo "$(BLUE)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(No_COLOR)"

clean:
	@echo "$(BLUE)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(No_COLOR)"
	@rm -rf $(OBJECTS)
	@echo "\033c"
	@echo "$(GREEN) OK $(No_COLOR)        $(RED) philo objects have been DELETED$(No_COLOR)"
	@echo "$(BLUE)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(No_COLOR)"

fclean: clean
	@rm -rf philo
	@echo "\033c"
	@echo "$(GREEN) OK $(No_COLOR)        $(RED) philo excutable DELETED$(No_COLOR)"
	@echo "$(BLUE)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(No_COLOR)"

re: fclean all

.PHONY: all clean fclean re 
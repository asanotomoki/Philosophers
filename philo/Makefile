# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 15:38:14 by asanotomoki       #+#    #+#              #
#    Updated: 2022/11/15 19:07:46 by asanotomoki      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo
OBJDIR   := ./obj
SRC_DIR := ./srcs
CC  := cc
CFLAGS := -Wall -Werror -Wextra -fsanitize=thread  -g

HEADERS :=  ./includes
INCLUDES :=	$(addprefix -I, $(HEADERS))

SRC_FILES = main.c init.c util.c works.c monitor.c work_util.c
SOURCES	:=  $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJECTS  := $(addprefix $(OBJDIR)/, $(SRC_FILES:.c=.o))
RM := rm -f
NAME_MSG := Compile $(NAME) 
CLEAN_MSG := Delete obj file
FCLEAN_MSG := Delete $(NAME) 

$(NAME): $(OBJECTS) 
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
	@echo $(NAME_MSG)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	@-mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

all: $(NAME)

clean:
	@rm -rf $(OBJDIR)
	@echo $(CLEAN_MSG)

fclean:	clean
	@$(RM) $(NAME)
	@echo $(FCLEAN_MSG)

re: fclean all

test1 : all
	./philo 5 800 200 200

test2 : all
	./philo 4 410 200 200 5

test3 : all
	./philo 4 310 200 200

.PHONY: all bonus fclean clean re test1 test2 test3

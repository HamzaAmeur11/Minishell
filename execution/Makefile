# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 18:05:22 by hmeur             #+#    #+#              #
#    Updated: 2022/09/21 19:52:06 by hmeur            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#______________MAKEFILE_______________

NAME := Minishell

HEADER := mini.h

CC := gcc

CFLAGS := #-Wall -Werror -Wextra

READLINE_FLAG := -lreadline

SRC :=	readline.c \
		comamnds.c \
		env.c \
		env_utils.c \
		exec_cmnds.c \
		ft_split.c \
		t_list.c \
		utils.c \
		redirection.c\
		init_cmnd.c


OBJS := $(SRC:.c=.o)

all :	$(NAME)
		@echo "Making Minishell"
		
$(NAME) :	$(OBJS)
			@$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(READLINE_FLAG)

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS)
	@echo "Removing objects files"

fclean : clean
	@rm -rf $(NAME)
	@echo "Removing Minishell"

re :	fclean all
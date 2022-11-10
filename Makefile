# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hameur <hameur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 18:05:22 by hmeur             #+#    #+#              #
#    Updated: 2022/11/10 19:09:31 by hameur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#______________MAKEFILE_______________

NAME := Minishell

HEADER := mini.h

CC := gcc

CFLAGS += -Wall -Werror -Wextra

LDFLAGS += -lreadline

SRC :=	main.c \
		commands/cd.c \
		commands/commands.c \
		commands/export.c \
		commands/unset.c \
		change_str.c \
		env_utils.c \
		env.c \
		exec_built.c \
		exec_cmnds.c \
		ft_free.c \
		ft_itoa.c \
		ft_split.c \
		init_cmnd.c \
		redirection.c\
		signals.c \
		split_pro_max.c \
		t_list.c \
		utils.c \
		utils1.c \
		utils2.c \


OBJS := $(SRC:.c=.o)

all :	$(NAME)
		@echo "Making Minishell"

$(NAME) :	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	@rm -rf $(OBJS)
	@echo "Removing objects files"

fclean : clean
	@rm -rf $(NAME)
	@echo "Removing Minishell"

re :	fclean all

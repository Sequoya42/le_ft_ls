#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/30 14:52:29 by rbaum             #+#    #+#              #
#    Updated: 2015/02/08 16:12:25 by rbaum            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY: clean, fclean, re

CC = gcc

CFLAG = -Wall -Wextra -Werror

NAME = ft_ls

SRC =	./srcs/add_link.c\
		./srcs/ft_adress.c\
		./srcs/ft_bool.c\
		./srcs/ft_ls.c\
		./srcs/ft_ls_l.c\
		./srcs/ft_pwd.c\
		./srcs/sort_list.c\
		./srcs/ft_ls_t.c\
		./srcs/ft_ls_aff.c\
		./srcs/sort_arg.c\
		./srcs/sort_list_rec.c\
		./srcs/ft_error.c

OBJ = $(subst srcs/,, $(SRC:.c=.o))

LIBFT = libft/

LIBFTEXE = $(LIBFT)libft.a

all: $(NAME)

$(OBJ): $(SRC)
		@$(CC) $(CFLAG) -I ./ -I  $(LIBFT)  -c $(SRC) 

$(NAME):  $(LIBFTEXE) $(OBJ)
		@$(CC) $(CFLAG) -L $(LIBFT) -lft -o $(NAME)  $(OBJ)
		@echo "ft_ls created"

$(LIBFTEXE): $(LIBFT)
		@make -C $(LIBFT)

clean:	
		@rm -f  $(OBJ)
		@make -C $(LIBFT) clean

fclean: 
		@rm -f  $(OBJ)	
		@rm -f $(NAME)
		@make -C $(LIBFT) fclean

re:		fclean all
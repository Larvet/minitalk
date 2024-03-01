# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: locharve <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 14:03:00 by locharve          #+#    #+#              #
#    Updated: 2024/03/01 14:14:01 by locharve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_C	:=	client
NAME_S	:=	server

CC		:=	cc

SRC_C	:=	client.c		\
			ft_atoi.c
SRC_S	:=	server.c		\
			ft_putchar_fd.c	\
			ft_putnbr_fd.c
SRC_A	:=	ft_memset.c		\
			ft_putstr_fd.c

HEADER	:=	minitalk.h

OBJ_C	:=	$(SRC_C:.c=.o)
OBJ_S	:=	$(SRC_S:.c=.o)
OBJ_A	:=	$(SRC_A:.c=.o)

CFLAGS	:=	-Wall -Werror -Wextra -g

all:		client server

client:		$(NAME_C)

$(NAME_C):	$(OBJ_C) $(OBJ_A)
	$(CC) $(CFLAGS) $(OBJ_C) $(OBJ_A) -o $(NAME_C)

server:		$(NAME_S)

$(NAME_S):	$(OBJ_S) $(OBJ_A)
	$(CC) $(CFLAGS) $(OBJ_S) $(OBJ_A) -o $(NAME_S)

%.o:		%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

fclean:		clean
	rm -f $(NAME_C) $(NAME_S)

clean:
	rm -f $(OBJ_C) $(OBJ_S) $(OBJ_A)

re:			fclean all

.PHONY:		all fclean clean re

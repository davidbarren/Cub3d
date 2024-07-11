# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbarrene <dbarrene@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:07:51 by dbarrene          #+#    #+#              #
#    Updated: 2024/07/11 18:54:07 by dbarrene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

LIBFTPATH = ./libft

LIBFT = $(LIBFTPATH)/libft.a
CC	= cc
CFLAGS = -Wall -Wextra -g -Werror #-fsanitize=address
SRCDIR = src
OBJDIR = obj
LIBFTPATH = libft
LIBMLX	:= ./MLX42
HEADERS	:= -I $(LIBMLX)/include

SRCS = $(SRCDIR)/main.c\

CSRCS = $(SRCDIR)/scene_loading.c\
		$(SRCDIR)/debug.c\
		$(SRCDIR)/errors.c\
		$(SRCDIR)/scene_parsing.c\
		$(SRCDIR)/freeing.c\

OBJS= $(SRCS:.c=.o)

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L "/home/$(USER)/.brew/opt/glfw/lib/"

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	
$(OBJS): $(SRCS)
	cc $(CFLAGS) -c $(@:.o=.c) -o $@

$(LIBFT):
	make -C $(LIBFTPATH)

$(NAME): $(LIBFT) $(OBJS)
	cc $(CFLAGS) $(SRCS) $(CSRCS) $(LIBS) $(INCLUDES) $(HEADERS) $(LIBFT) -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTPATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTPATH)
	@rm -rf $(LIBMLX)/build

re: fclean libmlx $(NAME)

.PHONY: all, clean, fclean, libmlx, re

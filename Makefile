# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:07:51 by dbarrene          #+#    #+#              #
#    Updated: 2024/08/14 12:07:40 by dzurita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d


CC	= cc
CFLAGS = -Wall -Wextra -g -Werror -Og #-fsanitize=address

SRCDIR = src
OBJDIR = obj
LIBFTPATH = ./libft
LIBMLX	:= ./MLX42


LIBFT = $(LIBFTPATH)/libft.a

SRCS = $(SRCDIR)/main.c\

CSRCS = $(SRCDIR)/scene_loading.c\
		$(SRCDIR)/debug.c\
		$(SRCDIR)/errors.c\
		$(SRCDIR)/scene_parsing.c\
		$(SRCDIR)/freeing.c\
		$(SRCDIR)/parsing_utils.c\
		$(SRCDIR)/scene_validation.c\
		$(SRCDIR)/gamestate.c\
		$(SRCDIR)/player_data.c\
		$(SRCDIR)/casting.c\

OBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(BSRCS))
COBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L "/home/$(USER)/.brew/opt/glfw/lib/"

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJDIR) $(COBJS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(COBJS) $(LIBS) $(INCLUDES) $(HEADERS) $(LIBFT) -o $@

$(LIBFT):
	make -C $(LIBFTPATH)

$(OBJDIR):
	@mkdir -p $(OBJDIR)


clean:
	rm -f $(OBJS) $(COBJS) $(BOBJS)
	rm -rf $(OBJDIR)
	make clean -C $(LIBFTPATH)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTPATH)
	@rm -rf $(LIBMLX)/build

re: fclean libmlx $(NAME)

.PHONY: all, clean, fclean, libmlx, re

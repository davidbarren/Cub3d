# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:07:51 by dbarrene          #+#    #+#              #
#    Updated: 2024/08/29 17:01:04 by dzurita          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
BNS_NAME = cub3D_bonus



CC	= cc
CFLAGS = -Wall -Wextra -g -Werror -O3


SRCDIR = mandatory
OBJDIR = obj
OBJBNSDIR = obj_bonus
BNSDIR = bonus
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
		$(SRCDIR)/textures.c\
		$(SRCDIR)/dda.c\
		$(SRCDIR)/render.c\
		$(SRCDIR)/movement.c\

CBNS_SRCS = $(BNSDIR)/scene_loading_bonus.c\
			$(BNSDIR)/debug_bonus.c\
			$(BNSDIR)/errors_bonus.c\
			$(BNSDIR)/scene_parsing_bonus.c\
			$(BNSDIR)/freeing_bonus.c\
			$(BNSDIR)/parsing_utils_bonus.c\
			$(BNSDIR)/scene_validation_bonus.c\
			$(BNSDIR)/gamestate_bonus.c\
			$(BNSDIR)/player_data_bonus.c\
			$(BNSDIR)/casting_bonus.c\
			$(BNSDIR)/textures_bonus.c\
			$(BNSDIR)/dda_bonus.c\
			$(BNSDIR)/lines_bonus.c\
			$(BNSDIR)/curso_mouse_bonus.c\
			$(BNSDIR)/mini_map_bonus.c\
			$(BNSDIR)/render_bonus.c\
			$(BNSDIR)/movement_bonus.c\

OBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(BSRCS))
COBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

LIBS := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L "$(HOME)/.brew/opt/glfw/lib/"

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

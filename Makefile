# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzurita <dzurita@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 09:07:51 by dbarrene          #+#    #+#              #
#    Updated: 2024/08/30 18:55:26 by dbarrene         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D


CC	= cc
CFLAGS = -Wall -Wextra -g -Werror -O3 #-fsanitize=address


SRCDIR = src
OBJDIR = obj
BONUSOBJ = bonus_obj
LIBFTPATH = ./libft
LIBMLX	:= ./MLX42
BONUSDIR = bonus
MLX_42 = $(LIBMLX)/build/libmlx42.a 
LIBFT = $(LIBFTPATH)/libft.a

SRCS = $(SRCDIR)/main.c\

CSRCS = $(SRCDIR)/scene_loading.c\
		$(SRCDIR)/errors.c\
		$(SRCDIR)/scene_parsing.c\
		$(SRCDIR)/freeing.c\
		$(SRCDIR)/parsing_utils.c\
		$(SRCDIR)/scene_validation.c\
		$(SRCDIR)/scene_utils.c\
		$(SRCDIR)/gamestate.c\
		$(SRCDIR)/player_data.c\
		$(SRCDIR)/casting.c\
		$(SRCDIR)/textures.c\
		$(SRCDIR)/dda.c\
		$(SRCDIR)/lines.c\
		$(SRCDIR)/render.c\
		$(SRCDIR)/movement.c\

BONUSSRC = $(BONUSDIR)/scene_loading_bonus.c\
		   $(BONUSDIR)/main_bonus.c\
		   $(BONUSDIR)/errors_bonus.c\
		   $(BONUSDIR)/scene_parsing_bonus.c\
		   $(BONUSDIR)/freeing_bonus.c\
		   $(BONUSDIR)/parsing_utils_bonus.c\
		   $(BONUSDIR)/scene_validation_bonus.c\
		   $(BONUSDIR)/scene_utils_bonus.c\
		   $(BONUSDIR)/gamestate_bonus.c\
		   $(BONUSDIR)/player_data_bonus.c\
		   $(BONUSDIR)/casting_bonus.c\
		   $(BONUSDIR)/textures_bonus.c\
		   $(BONUSDIR)/dda_bonus.c\
		   $(BONUSDIR)/lines_bonus.c\
		   $(BONUSDIR)/render_bonus.c\
		   $(BONUSDIR)/movement_bonus.c\

OBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS= $(patsubst $(BONUSDIR)/%.c, $(BONUSOBJ)/%.o, $(BONUSSRC))
COBJS= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

LIBS := $(MLX_42) -ldl -lglfw -pthread -lm -L "$(HOME)/.brew/opt/glfw/lib/"

all: $(NAME)

mlx_clone: 
	@if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

$(MLX_42): mlx_clone
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4;
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUSOBJ)/%.o: $(BONUSDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX_42) $(LIBFT) $(OBJDIR) $(COBJS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(COBJS) $(LIBS) $(INCLUDES) $(HEADERS) $(LIBFT) -o $@

$(LIBFT):
	make -C $(LIBFTPATH) --no-print-directory

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BONUSOBJ):
	@mkdir -p $(BONUSOBJ)

bonus: $(MLX_42) .bonus

.bonus: $(LIBFT) $(BONUSOBJ) $(BOBJS)
	$(CC) $(CFLAGS) $(BOBJS) $(LIBS) $(INCLUDES) $(HEADERS) $(LIBFT) -o $(NAME)
	@touch .bonus

clean:
	rm -f $(OBJS) $(COBJS) $(BOBJS)
	rm -rf $(OBJDIR)
	rm -rf $(BONUSOBJ)
	make clean -C $(LIBFTPATH)
	@rm -f .bonus

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTPATH)
	@rm -rf $(LIBMLX)/build

re: fclean $(NAME)

.PHONY: all, clean, fclean, libmlx, re, bonus, mlx_clone

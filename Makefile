# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 19:38:42 by azeraoul          #+#    #+#              #
#    Updated: 2021/04/13 07:56:55 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:=	$(shell uname)
ifeq ($(UNAME), Linux)
	LDFLAGS_P += -lXext -lX11
endif
ifeq ($(UNAME), Darwin)
	LDFLAGS_P += -lmlx -framework OpenGL -framework AppKit
endif

CC			:= gcc
RM			:= rm -rf
NAME		:= miniRT 

LIBFT_DIR	:= ./lib/libft/
LIBFT_NAME	:= libft.a
MLX_DIR		:= ./lib/mlx/
MLX_NAME	:= libmlx_Linux.a
INCS_DIR	:= ./includes/
MLX_NAME	:= libmlx.a
LDFLAGS		:= $(LDFLAGS_P) -lm -lpthread 
CFLAGS		:= -Wall -Wextra 
SRCS		:= $(addprefix ./srcs/, minirt.c vector_ope.c vector_norm.c inter.c multithreading.c \
			ray_tracer.c parser/parser_elem.c parser/parser_elem_nd.c \
			parser/parser_utils.c \
			scene_add.c scene_free.c scene_updater.c ray_tracer_nd.c \
			ray_tracer_rd.c inter_nd.c inter_rd.c grosrt.c)
INCS		:= $(addprefix ./includes/, minirt.h scene.h inter.h multithreading.h ray_tracer.h)
OBJS		:= $(SRCS:.c=.o)

all: 		$(NAME)

bonus:		$(NAME)

%.o: %.c 
			$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)include -c $< -o $@

$(NAME): $(OBJS) 
			make --silent -C $(MLX_DIR)
			make --silent -C $(LIBFT_DIR)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_DIR)$(MLX_NAME) $(LDFLAGS) -o $(NAME)

clean:
			make clean --silent -C $(LIBFT_DIR)
			$(RM) $(OBJS)

fclean:		clean
			make fclean --silent -C $(LIBFT_DIR)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 19:38:42 by azeraoul          #+#    #+#              #
#    Updated: 2021/04/16 16:04:13 by thezedzed        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
RM			:= rm -rf
NAME		:= miniRT 

LIBFT_DIR	:= ./lib/libft/
LIBFT_NAME	:= libft.a
MLX_DIR		:= ./lib/mlx/
INCS_DIR	:= ./includes/
MLX_NAME	:= libmlx.a
LDFLAGS		:= -lmlx -framework OpenGL -framework AppKit
CFLAGS		:= -Wall -Wextra -Werror 
SRCS		:= $(addprefix ./srcs/, minirt.c vector_ope.c vector_norm.c \
			inter.c multithreading.c ray_tracer.c parser/parser.c \
			parser/parser_elem.c parser/parser_utils.c parser/parser_utils2.c \
			hooks.c init.c parser/parser_shapes.c parser/parser_shapes2.c \
			parser/parser_shapes3.c scene_add.c scene_add2.c scene_free.c \
			scene_updater.c ray_tracer_nd.c ray_tracer_rd.c inter_nd.c \
			inter_rd.c grosrt.c)
OBJS		:= $(SRCS:.c=.o)

.PHONY:		all bonus clean fclean re
all: 		$(NAME)

bonus:		$(NAME)

%.o: %.c 
			@$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)include -c $< -o $@

$(NAME): $(OBJS) 
			@make --silent -C $(MLX_DIR)
			@make --silent -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_DIR)$(MLX_NAME) $(LDFLAGS) -o $@

clean:
			@make clean --silent -C $(LIBFT_DIR)
			@$(RM) $(OBJS)

fclean:		clean
			@make fclean --silent -C $(LIBFT_DIR)
			@$(RM) $(NAME)

re:			fclean all

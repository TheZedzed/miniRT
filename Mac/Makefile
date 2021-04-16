# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thezedzed <marvin@42.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/16 13:42:34 by thezedzed         #+#    #+#              #
#    Updated: 2021/04/16 13:42:36 by thezedzed        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
RM			:= rm -rf
NAME		:= miniRT 

LIBFT_DIR	:= ./lib/libft/
LIBFT_NAME	:= libft.a
INCS_DIR	:= ./includes/
LDFLAGS		:= -lmlx -framework OpenGL -framework AppKit -lm -lpthread 
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
			@$(CC) $(CFLAGS) -I$(INCS_DIR) -I$(LIBFT_DIR)include -c $< -o $@

$(NAME): $(OBJS) 
			@make --silent -C $(LIBFT_DIR)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(LDFLAGS) -o $@

clean:
			@make clean --silent -C $(LIBFT_DIR)
			@$(RM) $(OBJS)

fclean:		clean
			@make fclean --silent -C $(LIBFT_DIR)
			@$(RM) $(NAME)

re:			fclean all

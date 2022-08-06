# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 16:19:01 by jmehlig           #+#    #+#              #
#    Updated: 2022/08/06 21:24:27 by jmehlig          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

SRCS_PATH = srcs/

GET_NEXT_LINE_PATH = ./includes/get_next_line/

SRCS =	main.c \
		exit.c \
		parser.c \
		image.c \
		parser_setting.c \
		ft_stof.c \
		parser_utils.c \
		parser_figures.c \
		free.c

GET_NEXT_LINE_SRCS =	$(GET_NEXT_LINE_PATH)get_next_line.c \
						$(GET_NEXT_LINE_PATH)get_next_line_utils.c \

LIBFT = ${LIBFT_PATH}libft.a

OBJS_PATH = objs
OBJS = $(patsubst %.c, %.o, $(SRCS))

LIBFT_PATH	= ./includes/libft/

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror -D BUFFER_SIZE=1

MLXFLAGS =		./minilibx_macos/libmlx.a -framework OpenGL -framework AppKit

all:	$(NAME)

${LIBFT}:
	@make -C $(LIBFT_PATH)

$(NAME): ${LIBFT} $(addprefix $(SRCS_PATH), $(SRCS))
	$(CC) $(CFLAGS) -c $(GET_NEXT_LINE_SRCS) $(addprefix $(SRCS_PATH), $(SRCS))
	@mkdir -p $(OBJS_PATH)
	@mv $(OBJS) $(OBJS_PATH) 
	$(CC) $(CFLAGS) $(addprefix $(OBJS_PATH)/, $(OBJS)) $(GET_NEXT_LINE_SRCS) ${LIBFT_PATH}libft.a -o $(NAME)

clean:
			make clean -C $(LIBFT_PATH)
			rm -rf $(OBJS_PATH)
			rm *.o

fclean_libft:
			make fclean -C $(LIBFT_PATH)

fclean:		clean fclean_libft
			$(RM) $(NAME)

re:			fclean
			$(MAKE)

.PHONY:	target_libft
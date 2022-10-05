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
		free.c \
		graphic.c \
		graphic_utils.c \
		math.c\
		intersection.c\
		intersection_cylinder.c\
		color.c\

GET_NEXT_LINE_SRCS =	get_next_line.c \
						get_next_line_utils.c \

LIBFT = ${LIBFT_PATH}libft.a

MLX = $(MLX_PATH)libmlx.a

OBJS_PATH = objs
OBJS = $(patsubst $(SRCS_PATH)/%.c, $(OBJS_PATH)/%.o, $(addprefix $(SRCS_PATH), $(SRCS)))
#$(addprefix $(OBJS_PATH)/, $(SRCS):%.c=%.o))

OBJS_GNL = $(patsubst %.c, %.o, $(GET_NEXT_LINE_SRCS))

LIBFT_PATH	= ./includes/libft/

MLX_PATH = ./minilibx_macos/

CC		=		gcc

CFLAGS	=		-Wall -Wextra -Werror -D BUFFER_SIZE=1

MLXFLAGS =		$(MLX) -framework OpenGL -framework AppKit

all:	obj $(NAME)

${LIBFT}:
	@make -C $(LIBFT_PATH)

mlx:
	@make -C $(MLX_PATH)

obj:
	@mkdir -p $(OBJS_PATH)

$(NAME): ${LIBFT} $(OBJS)
	$(CC) $(CFLAGS) -c $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) $(addprefix $(SRCS_PATH), $(SRCS))
	@mv *.o $(OBJS_PATH) 
	$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) ${LIBFT_PATH}libft.a -o $(NAME) -I $(MLX_PATH)

clean:
			make clean -C $(LIBFT_PATH)
			rm -rf $(OBJS_PATH)

fclean_libft:
			make fclean -C $(LIBFT_PATH)


fclean:		clean fclean_libft
			$(RM) $(NAME)

re:			fclean
			$(MAKE)

.PHONY:	target_libft
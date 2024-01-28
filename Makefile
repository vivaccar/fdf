SRCS	=	srcs/close.c srcs/draw.c srcs/ft_atoi_base.c srcs/initialize.c \
			srcs/keyboard.c srcs/main.c srcs/read_map.c srcs/utils.c \
			srcs/events.c srcs/utils2.c \
			srcs/get_next_line/get_next_line.c srcs/get_next_line/get_next_line_utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	fdf
MLX		=	./minilibx-linux
MLXA	=	$(MLX)/libmlx_Linux.a
LIBFTA	=	./srcs/Libft/libft.a 
LIBFTD	=	./srcs/Libft

all: $(NAME)

$(NAME): $(LIBFTA) $(MLXA) $(OBJS)
	$(CC) -g $(OBJS) $(LIBFTA) -lmlx_Linux -L$(MLX) -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(MLXA):
	make -C $(MLX)

$(LIBFTA): $(LIBFTD)
	make -C $(LIBFTD)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFTD)
	make clean -C $(MLX)

fclean: clean
	rm -f $(NAME)
	make clean -C $(LIBFTD)
	make clean -C $(MLX)
	rm -f $(LIBFTA)

re: fclean all


	

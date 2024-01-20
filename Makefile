SRCS	=	get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			main.c read_map.c initialize.c close.c draw.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	fdf
MLX		=	./minilibx-linux
MLXA	=	$(MLX)/libmlx_Linux.a
LIBFTA	=	./Libft/libft.a 
LIBFTD	=	./Libft

all: $(NAME)

$(NAME): $(OBJS) $(MLXA) $(LIBFTA)
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

	

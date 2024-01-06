SRCS	=	main.c

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	fdf
MLX		=	./minilibx-linux
MLXA	=	$(MLX)/libmlx_Linux.a

all: $(NAME)

$(NAME): $(OBJS) $(MLXA)
	$(CC) $(OBJS) -lmlx_Linux -L$(MLX) -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(MLXA):
	make -C $(MLX)

clean:
	rm -f $(OBJS)
	make -C $(MLX) clean

fclean: clean
	rm -f $(NAME)
	make -C $(MLX) clean

re: fclean all

	

SRCS	=	$(wildcard $(shell find srcs -type f -name '*.c'))

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra

NAME	=	fdf
MLX		=	./minilibx-linux
MLXA	=	$(MLX)/libmlx_Linux.a
LIBFTA	=	./srcs/Libft/libft.a 
LIBFTD	=	./srcs/Libft

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

	

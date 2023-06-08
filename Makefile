NAME = cub3D

SRC =	abouassi/cub3D.c\
		abouassi/cub3D_parce.c\
		abouassi/free_err.c\

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g

RM = rm -rf

CC = cc

all	: ${NAME}

${NAME} : ${OBJ}
		make -C libft
		${CC} ${CFLAGS} ${OBJ} libft/libft.a -o ${NAME}

clean :
	make clean -C libft
	$(RM) $(OBJ) 
	
fclean	:	clean
		make fclean -C libft
		$(RM) $(NAME)

re	:	fclean all
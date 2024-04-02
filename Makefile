NAME			=	serveur	
NAME_CLIENT		=	client
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
SRC				=	src/serveur.c
SRC_CLIENT		=	src/client.c
OBJ				=	${SRC:.c=.o}
OBJ_CLIENT		=	${SRC_CLIENT:.c=.o}
MAKE_LIBFT		=	@make -C libft
LIBFT			=	libft/libft.a

all: $(NAME) $(NAME_CLIENT)

$(NAME): $(OBJ)
	$(MAKE_LIBFT)
	$(MAKE_LIBFT) bonus
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(MAKE_LIBFT)
	$(MAKE_LIBFT) bonus
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

clean:
	rm -rf $(OBJ) $(OBJ_CLIENT)
	$(MAKE_LIBFT) clean

fclean:	clean
	rm -rf $(NAME) $(NAME_CLIENT)
	$(MAKE_LIBFT) fclean

re : fclean all

.PHONY: all, clean, fclean, re
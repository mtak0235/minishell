NAME	= test

SRC_NAME = mtak.c shell.c

SRC_PATH = ./
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(CFLAG) $(HEADER) -o $@ -c $<

CFLAG	= -Wall -Wextra -Werror -lncurses

LIBFT	= libft.a

LIBS	= -L./libft -lft 

RM	= rm -rf

all	: $(NAME)

$(NAME)	: $(OBJ) $(LIBFT) $(LIBMLX)
	gcc -o $(NAME) $(OBJ) $(HEADER) $(CFLAG) $(LIBS)

$(LIBFT):
	$(MAKE) -C ./libft

clean	:
	$(MAKE) -C ./libft clean
	rm -rf $(OBJ_PATH) $(SCREENSHOT)

fclean	: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re		: fclean all

.PHONY: all clean fclean re
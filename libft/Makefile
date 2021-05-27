# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seokim <seokim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/01 23:48:27 by seokim            #+#    #+#              #
#    Updated: 2021/01/02 20:07:34 by seokim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=gcc
CFLAGS=-Wall -Wextra -Werror

MAN=ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha \
	 ft_isascii ft_isdigit ft_isprint ft_itoa ft_memccpy \
	 ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset \
	 ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd \
	 ft_split ft_strchr ft_strdup ft_strjoin ft_strlcat \
	 ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr \
	 ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper

BONUS=ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
	  ft_lstdelone ft_lstclear ft_lstiter ft_lstmap \
	  ft_lstadd_back

SRCS=$(addsuffix .c, $(MAN))
SRCS_BO=$(addsuffix .c, $(BONUS))
OBJECTS=$(addsuffix .o, $(MAN))
OBJECTS_BO=$(addsuffix .o, $(BONUS))

ifdef WITH_BONUS
	SRC_FILES=$(SRCS) $(SRCS_BO)
	OBJ_FILES=$(OBJECTS) $(OBJECTS_BO)
else
	SRC_FILES=$(SRCS)
	OBJ_FILES=$(OBJECTS)
endif

all: $(NAME)

$(NAME): $(SRC_FILES) libft.h
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	ar rcs $(NAME) $(OBJ_FILES)

bonus:
	make WITH_BONUS=1 all

clean:
	rm -f $(OBJECTS) $(OBJECTS_BO)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
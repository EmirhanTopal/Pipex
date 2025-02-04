NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
FILES = pipex.c \
		utils.c \
		utils2.c \

OBJECTS = $(FILES:.c=.o)

all: ${NAME}

$(NAME): $(OBJECTS) 
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
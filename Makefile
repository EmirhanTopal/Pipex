NAME = pipex
CC = cc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror
FILES = pipex.c \
	ft_utils.c \
	ft_utils_2.c \
	ft_process.c

OBJS = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
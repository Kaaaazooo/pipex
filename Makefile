NAME = pipex

CC = gcc

OPTIONS = -I . -I utils
CFLAGS = -Wall -Werror -Wextra $(OPTIONS)

UTILS = $(addprefix utils/, ft_calloc.c ft_memcpy.c ft_putdstr.c ft_split.c ft_strcmp.c \
			ft_strcpy.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strndup.c)

SRCS = main.c $(UTILS)

BONUS_SRCS = main_bonus.c $(UTILS)

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(BONUS_OBJS)

clean:
	rm -rf $(OBJS)
	rm -rf $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = pipex.c	pipex_utils.c	pipex_utils1.c	pipex_utils2.c

SRC_BONUS = pipex_bonus.c	pipex_utils_bonus.c	pipex_utils.c	pipex_utils1.c	pipex_utils2.c	get_next_line_utils.c	get_next_line.c

OBJS = $(SRC:.c=.o)

OBJS_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(OBJS_BONUS)
	$(CC) $(CFLAGS) $^ -o pipex_bonus

%.o:%.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) pipex_bonus

re: fclean all

.PHONY: all clean fclean re

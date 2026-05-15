CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = codexion

SRC = main.c \
		coder/coder.c \
		parser/parser.c \
		usage.c \
		codexion.c \

all: $(NAME)

OBJS := $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)

debug: CFLAGS = -DDEBUG
debug: all
	./$(NAME) 3 600 50 50 50 20 5 fifo

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.SILENT: $(NAME)
.PHONY: all debug clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = codexion

SRC = main.c \
		utils/utils.c \
		coder/coder.c \
		coder/coder_utils.c \
		dongle/dongle.c \
		parser/parser.c \
		usage.c \
		codexion.c \

all: $(NAME)

OBJS := $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)

debug: CFLAGS = -DDEBUG
debug: all
	./$(NAME) 4 600 50 50 50 2 150 fifo

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.SILENT: $(NAME)
.PHONY: all debug clean fclean re

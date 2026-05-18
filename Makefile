CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

NAME = codexion

SRC = main.c \
		usage.c \
		codexion.c \
		utils/utils.c \
		coder/coder.c \
		dongle/dongle.c \
		parser/parser.c \
		coder/coder_utils.c \
		scheduler/scheduler.c \

all: $(NAME)

OBJS := $(SRC:%.c=%.o)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS)

debug: CFLAGS = -DDEBUG
debug: all
	./$(NAME) 4 600 50 50 50 2 150 fifo

test_fifo: all
	./$(NAME) 3 600 150 50 50 10 10 fifo

test_edf: all
	./$(NAME) 4 600 50 50 50 2 150 edf

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.SILENT: $(NAME)
.PHONY: all debug clean fclean re test_fifo test_edf

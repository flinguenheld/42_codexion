CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = codexion
LIBFT_FOLDER = ./libft/
LIBFT_FILE = $(LIBFT_FOLDER)libft.a

SRC = main.c \
		usage.c \
		parser/parser.c \

all: $(NAME)

OBJS := $(SRC:%.c=%.o)

$(NAME): libft $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT_FILE)

libft:
	@make -C $(LIBFT_FOLDER) --no-print-directory

debug: CFLAGS = -DDEBUG
debug: all
	./$(NAME) 20 600 50 50 50 20 5 fifo

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_FOLDER) clean --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_FOLDER) fclean --no-print-directory

re: fclean all

.SILENT: $(NAME)
.PHONY: all libft debug clean fclean re

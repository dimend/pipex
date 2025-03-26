CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./includes -I./src/libft

TARGET = pipex

OBJ_PATH = obj/
LIBFT_DIR = src/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

SRCS =	src/pipex.c \
		src/utils.c \
		src/error_handling.c
		
OBJS = $(SRCS:src/%.c=$(OBJ_PATH)%.o)
HEADERS = includes/pipex.h

$(OBJ_PATH)%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT_LIB) $(TARGET)

$(TARGET): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(TARGET)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(TARGET)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

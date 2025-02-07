CC = cc

CFLAGS = -Wall -Wextra -Werror -g -I./includes

TARGET = pipex

OBJ_PATH = obj/

SRCS =	src/pipex.c

OBJS = $(SRCS:src/%.c=$(OBJ_PATH)%.o)

HEADERS = includes/pipex.h

$(OBJ_PATH)%.o: src/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: 
	rm -f $(OBJS) $(TARGET)

re: fclean all

.PHONY: all clean fclean re

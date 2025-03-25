# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 19:39:40 by dimendon          #+#    #+#              #
#    Updated: 2024/11/13 18:33:06 by dimendon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

TARGET = libft.a

# All source files (regular + bonus)
SRCS = \
    ft_atoi.c \
    ft_isascii.c \
    ft_strchr.c \
    ft_strrchr.c \
    ft_isalnum.c \
    ft_isdigit.c \
    ft_strlen.c \
    ft_tolower.c \
    ft_isalpha.c \
    ft_isprint.c \
    ft_strncmp.c \
    ft_toupper.c \
    ft_memset.c \
    ft_bzero.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_strlcpy.c \
    ft_strlcat.c \
    ft_strcatrealloc.c \
    ft_substr.c \
    ft_strnstr.c \
    ft_calloc.c \
    ft_strdup.c \
    ft_strjoin.c \
    ft_strtrim.c \
    ft_split.c \
    ft_itoa.c \
    ft_strmapi.c \
    ft_striteri.c \
    ft_putchar_fd.c \
    ft_putstr_fd.c \
    ft_putendl_fd.c \
    ft_putnbr_fd.c \
    ft_lstnew_bonus.c \
    ft_lstadd_front_bonus.c \
    ft_lstsize_bonus.c \
    ft_lstlast_bonus.c \
    ft_lstadd_back_bonus.c \
    ft_lstdelone_bonus.c \
    ft_lstclear_bonus.c \
    ft_lstiter_bonus.c \
    ft_lstmap_bonus.c  \
    ft_strtok.c

# All object files
OBJS = $(SRCS:.c=.o)

HEADERS = libft.h

# Default target to create the static library
all: $(TARGET)

# Create the static library with all object files (regular + bonus)
$(TARGET): $(OBJS)
	ar -crs $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Remove object files and the static library
fclean: clean
	rm -f $(TARGET)

# Rebuild everything from scratch
re: fclean all

# Declare non-file targets
.PHONY: all clean fclean re


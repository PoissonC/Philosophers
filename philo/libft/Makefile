# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror 

SRCS := ./ft_isalpha.c \
		./ft_memcmp.c \
		./ft_strlcat.c \
		./ft_strrchr.c \
		./ft_atoi.c \
		./ft_isascii.c \
		./ft_memcpy.c \
		./ft_strlcpy.c \
		./ft_tolower.c \
		./ft_atoi.o  \
		./ft_isdigit.c \
		./ft_memmove.c \
		./ft_strlen.c \
		./ft_toupper.c \
		./ft_bzero.c \
		./ft_isprint.c \
		./ft_memset.c \
		./ft_strncmp.c \
		./ft_isalnum.c \
		./ft_memchr.c  \
		./ft_strchr.c  \
		./ft_strnstr.c \
		./ft_calloc.c \
		./ft_strdup.c \
		./ft_substr.c \
		./ft_strjoin.c \
		./ft_strtrim.c \
		./ft_split.c \
		./ft_itoa.c \
		./ft_strmapi.c \
		./ft_striteri.c \
		./ft_putchar_fd.c \
		./ft_putstr_fd.c \
		./ft_putendl_fd.c \
		./ft_putnbr_fd.c \
		./ft_printf.c \
		./ft_printtool.c \
		./ft_freestrarr.c \
		./get_next_line.c \
		./get_next_line_utils.c
SRCS_BONUS := ./ft_lstnew.c \
			  ./ft_lstadd_front.c \
			  ./ft_lstsize.c \
			  ./ft_lstlast.c \
			  ./ft_lstadd_back.c \
			  ./ft_lstdelone.c \
			  ./ft_lstclear.c \
			  ./ft_lstiter.c \
			  ./ft_lstmap.c

OBJS := $(SRCS:.c=.o)
OBJS_BONUS := $(SRCS_BONUS:.c=.o)
OBJS_ALL := $(OBJS) $(OBJS_BONUS)

# Target library
NAME := libft.a

# Default rule: make all
all: bonus

# Rule to build the library
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

# Rule to compile object files
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS_ALL)


# Clean up object files and the library
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

bonus: $(OBJS_ALL)
	ar -rcs $(NAME) $(OBJS_ALL)

# By default, just run 'make all'
.DEFAULT_GOAL := all
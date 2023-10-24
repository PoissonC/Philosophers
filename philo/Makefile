# Compiler and flags
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
# Sources
SRC_PATH	=	src/
SRC			=	main.c parsing.c checker.c utils.c create.c action.c manager.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
# Objects
OBJ_PATH	= 	src/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
# Target
NAME 		= philo

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC			=	-I ./src\
				-I ./libft/\
# Default rule: make all
all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)
# Rule to build the library
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -lpthread
# Rule to compile object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Clean up object files
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_PATH)
# Clean up object files and the library
fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(NAME)
# Rebuild everything
re: fclean all

# By default, just run 'make all'
.DEFAULT_GOAL := all
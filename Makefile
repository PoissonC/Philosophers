# Compiler and flags
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
# Sources
SRC_PATH	=	src/
SRC			=	main.c parsing.c checker.c utils.c create.c action.c manager.c ft_atoi.c ft_tools.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))
# Objects
OBJ_PATH	= 	src/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))
# Target
NAME 		= philo

# Includes
INC			=	-I ./src\
				-I ./libft/
# Default rule: make all
all: $(NAME)

# Rule to build the library
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(INC) -lpthread
# Rule to compile object files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(SRC_PATH)philo.h
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Clean up object files
clean:
	rm -f $(OBJS)
# Clean up object files and the library
fclean: clean
	rm -f $(NAME)
# Rebuild everything
re: fclean all

# By default, just run 'make all'
.DEFAULT_GOAL := all
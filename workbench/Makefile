#
# Nombre del programa
NAME = pipex

# Flags al compilar
FLAGS = -g -Wall -Wextra -Werror 
TESTFLAGS = -fsanitize=address -g

# DIRs
SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = include/
LIBFT_DIR = libft/

# Sources files
SRC_FILE = init.c utils.c main.c
OBJ_FILE = $(SRC_FILE:.c=.o)
INC_FILE = pipex.h

# Elements
SRC	= $(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_FILE))
INC = $(addprefix $(INC_DIR), $(INC_FILE))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Test
TEST_DIR = test/
TEST_FILE = main.c init.c utils.c
TEST = $(addprefix $(TEST_DIR), $(TEST_FILE))
TEST_OUT = trymebabe.out

# Flags for linking
LNK = ar rc

#### Compilacion del programa ####

all: $(LIBFT) $(NAME) 

#obj:
#@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(INC) $(LIBFT)
	@echo Creating program $(NAME)...
	cc -o $(NAME) $(FLAGS) $(SRC) -I$(INC_DIR) -L$(LIBFT_DIR) -lft 

#$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC) Makefile
#gcc $(FLAGS) -c $< -I$(INC_DIR) -Llibft -lft -o $@

test: re all
	echo "applying following commands to exec\n" && cat a.sh
	./a.sh
#gcc -o $(TEST_OUT) $(TESTFLAGS) $(TEST) -I$(INC_DIR) -Llibft -lft 

# mostrar a Martin
#update_gitignore:
#echo '$(TEST_OUT)' >> ../.gitignore

fclean: clean
	@rm -f $(NAME) 
	@rm -f $(LIBFT)
	@rm -f $(TEST_OUT)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re obj test

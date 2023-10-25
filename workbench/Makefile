#
# Nombre del programa
NAME = pipex

# Flags al compilar
#FLAGS = -g -Wall -Wextra -Werror 

# DIRs
SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = include/
LIBFT_DIR = libft/

# Sources files
SRC_FILE = parsing.c utils.c handle.c
OBJ_FILE = $(SRC_FILE:.c=.o)
INC_FILE = pipex.h

# Elements
SRC	= $(addprefix $(SRC_DIR), $(SRC_FILE))
OBJ	= $(addprefix $(OBJ_DIR), $(OBJ_FILE))
INC = $(addprefix $(INC_DIR), $(INC_FILE))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Test
TEST_DIR = test/
TEST_FILE = pathtesting.c
TEST = $(addprefix $(TEST_DIR), $(TEST_FILE))
TEST_OUT = trymebabe.out

# Flags for linking
LNK = ar rc

#### Compilacion del programa ####

all: obj $(LIBFT) $(NAME) 

obj:
	@mkdir -p $(OBJ_DIR)

libft:
	make -C $(LIBFT_DIR)
	make clean -C $(LIBFT_DIR)

$(NAME): $(OBJ) 
	@echo Creating program $(NAME)...
	cc $(OBJ) -o $(NAME) -L$(LIBFT_DIR) -lft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC) Makefile
	gcc $(FLAGS) -c $< -I$(INC_DIR) -Llibft -lft -o $@

test: fclean libft Makefile
	gcc $(FLAGS) $(TEST) -I$(INC_DIR) -Llibft -lft -o $(TEST_OUT)

# mostrar a Martin
#update_gitignore:
#echo '$(TEST_OUT)' >> ../.gitignore

fclean: clean
	@rm -f $(NAME) 
	@rm -f $(LIBFT)
	@rm -f $(TEST_OUT)

clean:
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re obj libft test

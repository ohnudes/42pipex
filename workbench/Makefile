#
# Nombre del programa
NAME = pipex

# Flags al compilar
FLAGS = -g -Wall -Wextra -Werror 

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

# Flags for linking
LNK = ar rc

#### Compilacion del programa ####

all: obj $(NAME) 

$(NAME): $(OBJ) 
	@echo Creating library $(NAME)...
	$(LNK) $@ $^ 

obj: libft
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) Makefile
	gcc $(FLAGS) -I $(INC_DIR) -c $< -o $@ -Llibft -lft  

libft:
	make -C $(LIBFT_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME) 

clean:
	@rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re obj libft

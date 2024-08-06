SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

HDR_FLAGS = -I $(LIBMLX)/include -I $(LIBFT) -I $(FT_PRINTF) -I .
LIB_FLAGS = -ldl -lglfw -pthread -lm -L $(PWD)/$(LIB_DIR) -lft -lftprintf -lmlx42 -rpath $(PWD)/$(LIB_DIR)

BUILD_DIR = build
LIB_DIR = lib

NAME = fdf
CFLAGS = -Wall -Wextra -Werror -Ofast -g

CC = clang
LIBMLX = MLX42
LIBFT = libft
FT_PRINTF = ft_printf

all: $(NAME)

libft: | $(LIB_DIR) $(INC_DIR)
	make -C $(LIBFT)
	ln -sf $(CURDIR)/$(LIBFT)/libft.so $(LIB_DIR)

ft_printf: | $(LIB_DIR) $(INC_DIR)
	make -C $(FT_PRINTF)
	ln -sf $(CURDIR)/$(FT_PRINTF)/libftprintf.so $(LIB_DIR)

libmlx: | $(LIB_DIR) $(INC_DIR)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	ln -sf $(CURDIR)/$(LIBMLX)/build/libmlx42.a $(LIB_DIR)

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(HDR_FLAGS)

$(BUILD_DIR) $(LIB_DIR) $(INC_DIR):
	mkdir -p $@

$(NAME): libft libmlx ft_printf $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIB_FLAGS) $(HDR_FLAGS) -o $(NAME)

clean reclean:
	rm -rf $(OBJS)
	make -C $(LIBFT) clean
	make -C $(FT_PRINTF) clean

fclean: clean
	rm -rf $(NAME) $(LIB_DIR)
	make -C $(LIBFT) fclean
	make -C $(FT_PRINTF) fclean

re: fclean all reclean

.PHONY: all clean fclean re libmlx libft ft_printf

MAKE = @make --no-print-directory

CC = cc
IFLAGS = -Iheaders/
CFLAGS = -g3 -Werror -Wall -Wextra ${IFLAGS}
NAME = cub3D

HEADER = ./headers/cube3d.h ./headers/parsing.h
SRC_DIR=src/

SRC_LIST= upscaling.c keyboard.c casting_utils.c main.c map_gen.c sprite.c raycast.c draw.c draw_utils.c
SRC_LIST_P = parse_keys.c parse_map.c parse_color.c parsing.c parse_keys_utils.c setup_map.c parse_map_utils.c parsing_utils.c inits_textures.c map_autotile.c map_autotile_utils.c map_inits.c
SRC=$(addprefix $(SRC_DIR),$(SRC_LIST)) \
	$(addprefix $(SRC_DIR)parsing/,$(SRC_LIST_P))
OBJ_DIR=obj/
OBJ=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

INCLUDE = -L libft -l ft -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
LIBFT_DIR=libft/
LIBFT_SRC = ft_free_splited.c ft_realloc.c ft_striteri.c ft_strmapi.c ft_strtrim.c ft_split.c ft_itoa.c ft_strjoin.c ft_substr.c ft_strnstr.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_calloc.c ft_strdup.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_printf/ft_printf.c ft_printf/ft_put.c get_next_line/get_next_line.c ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c
LIBFT_SRC_FULL = $(addprefix $(LIBFT_DIR),$(LIBFT_SRC))
LIBFT = $(LIBFT_DIR)libft.a

MINILIBX = minilibx-linux/libmlx_Linux.a

NB_FILES=$(words $(OBJ))

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@echo -n $(BLUE)"[$$(echo "scale=2; $$(find $(OBJ_DIR) -maxdepth 2 -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(GREEN)
endef

define prompt
	@echo -e $1"\n================ $2 ================\n"$(END_COLOUR)
endef

define normitest
	@echo -e $(BLUE)"Test norminette..."$(END_COLOUR)
	@if norminette $(SRC_DIR) $(HEADER) $(LIBFT_SRC_FULL) | grep Error; then \
		echo -e $(RED)"\n================ Norminette KO ================"$(END_COLOUR); \
	else \
		echo -e $(GREEN)"\n================ Norminette OK ================"$(END_COLOUR); \
	fi
endef

define gitignore_gen
	@if test .gitignore ; then\
		echo -e "*.o\n$(NAME)" > .gitignore; \
	fi ;
endef

.PHONY: all clean fclean re

all :
	$(call normitest)
	$(call prompt,$(BLUE),"Creating $(NAME)")
	$(MAKE) $(NAME)

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c Makefile $(HEADER)
	$(call percent)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo -n $(END_COLOUR)

$(NAME) : $(MINILIBX) $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(call percent)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INCLUDE)
	@echo -n $(END_COLOUR)
	$(call prompt,$(GREEN),"$(NAME) compiled")

$(LIBFT) : $(LIBFT_SRC_FULL) libft/libft.h
	$(MAKE) libft.a -C libft

$(MINILIBX) :
	$(MAKE) -C minilibx-linux

$(OBJ_DIR):
	@mkdir -p $(sort $(dir ${OBJ}))

clean :
	@echo -e $(BLUE)Cleaning...$(END_COLOUR)
	@$(MAKE) fclean -C libft
	@$(MAKE) clean -C minilibx-linux
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)
	$(call prompt,$(GREEN),"$(NAME) cleared")

re :
	$(MAKE) fclean
	$(MAKE) all

run :
	$(MAKE) all
	@./$(NAME) 42.cub

debug :
	$(MAKE) libft.a -C libft FLAG="$(FLAG) -g3"
	$(MAKE) re FLAG="$(FLAG) -g3"
	@gdb -tui $(NAME)

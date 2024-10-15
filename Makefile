MAKE = @make --no-print-directory

CC = cc
FLAG = -Werror -Wall -Wextra -g3
NAME = cube3d

HEADER = ./headers/$(NAME).h ./headers/parsing.h
SRC_DIR=src/
SRC_LIST= main.c map_gen.c parse_keys.c parse_map.c parse_color.c parsing.c parse_keys_utils.c
SRC=$(addprefix $(SRC_DIR),$(SRC_LIST))
OBJ_DIR=obj/
OBJ=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

INCLUDE = -L libft -l ft -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
LIBFT_DIR=libft/
LIBFT_SRC = ft_free_splited.c ft_realloc.c ft_striteri.c ft_strmapi.c ft_strtrim.c ft_split.c ft_itoa.c ft_strjoin.c ft_substr.c ft_strnstr.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_calloc.c ft_strdup.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_printf/ft_printf.c ft_printf/ft_put.c get_next_line/get_next_line.c
LIBFT_SRC_FULL = $(addprefix $(LIBFT_DIR),$(LIBFT_SRC))
LIBFT = $(LIBFT_DIR)libft.a

MINILIBX = minilibx-linux/libmlx_Linux.a

NB_FILES=$(words $(SRC_LIST))

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@echo -n $(BLUE)"[$$(echo "scale=2; $$(find $(OBJ_DIR) -maxdepth 1 -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(GREEN)
endef

define prompt
	@echo $1"\n================ $2 ================\n"$(END_COLOUR)
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
#	$(call normitest)
	$(call prompt,$(BLUE),"Creating $(NAME)")
	$(MAKE) $(NAME)

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c Makefile $(HEADER)
	$(call percent)
	$(CC) $(FLAG) -c $< -o $@
	@echo -n $(END_COLOUR)

$(NAME) : $(MINILIBX) $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(call percent)
	$(CC) $(FLAG) -o $@ $(OBJ) $(INCLUDE)
	@echo -n $(END_COLOUR)
	$(call prompt,$(GREEN),"$(NAME) compiled")

$(LIBFT) : $(LIBFT_SRC_FULL) libft/libft.h
	$(MAKE) libft.a -C libft

$(MINILIBX) :
	$(MAKE) -C minilibx-linux

$(OBJ_DIR):
	@mkdir $@

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

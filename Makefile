MAKE = @make --no-print-directory
ECHO = echo -e

CC = cc
IFLAGS = -Iheaders/
CFLAGS = -Werror -Wall -Wextra ${IFLAGS} -O2 -DHEIGHT_WIN=$(SCREEN_HEIGHT) -DWIDTH_WIN=$(SCREEN_WIDTH)
NAME = cub3D
NAME_BONUS = $(NAME)_bonus
HEADER = ./headers/cube3d.h ./headers/parsing.h ./headers/types.h
SRC_DIR=src/

SRC_LIST_COMMON:= init.c keyboard.c casting_utils.c main.c sprite.c draw_utils.c
SRC_LIST_MANDATORY:= frame_update.c raycast.c draw.c
SRC_LIST_P:= parse_keys.c parse_map.c parse_color.c parsing.c parse_keys_utils.c setup_map.c parse_map_utils.c parsing_utils.c inits_textures.c
SRC_LIST_BONUS:= upscaling.c map_autotile_bonus.c map_autotile_utils_bonus.c bonus.c mouse_bonus.c draw_bonus.c floor_ceilling_ray_bonus.c frame_update_bonus.c raycast_bonus.c map_gen_bonus.c map_inits_bonus.c

SRC_COMMON=$(addprefix $(SRC_DIR),$(SRC_LIST_COMMON)) $(addprefix $(SRC_DIR)parsing/,$(SRC_LIST_P))
SRC_MANDATORY= $(addprefix $(SRC_DIR),$(SRC_LIST_MANDATORY)) $(SRC_COMMON)
SRC_BONUS:= $(addprefix $(SRC_DIR)bonus/,$(SRC_LIST_BONUS)) $(SRC_COMMON)

OBJ_DIR=obj/
OBJ_MANDATORY=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_MANDATORY))
OBJ_COMMON=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_COMMON))
OBJ_DIR_BONUS=$(OBJ_DIR)bonus
OBJ_BONUS=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_BONUS))

INCLUDE = -L libft -l ft -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm
LIBFT_DIR=libft/
LIBFT_SRC = ft_free_splited.c ft_realloc.c ft_striteri.c ft_strmapi.c ft_strtrim.c ft_split.c ft_itoa.c ft_strjoin.c ft_substr.c ft_strnstr.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_calloc.c ft_strdup.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_printf/ft_printf.c ft_printf/ft_put.c get_next_line/get_next_line.c ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c
LIBFT_SRC_FULL = $(addprefix $(LIBFT_DIR),$(LIBFT_SRC))
LIBFT = $(LIBFT_DIR)libft.a

MINILIBX = minilibx-linux/libmlx_Linux.a

NB_FILES=$(words $(OBJ_COMMON) $(OBJ_MANDATORY))

NB_FILES_BONUS=$(words $(OBJ_BONUS))
NB_OBJ := $(words $(wildcard obj/*.o obj/parsing/*.o obj/bonus/*.o))

SCREEN_HEIGHT := $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2))
SCREEN_WIDTH := $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1))

RAYCAST_HEIGHT := $(shell expr $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2)) / 4)
RAYCAST_WIDTH := $(shell expr $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1)) / 4)

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@echo -n $(BLUE)"[$$(echo "scale=2; $$(find $(OBJ_DIR) -maxdepth 2 -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(GREEN)
endef

define prompt
	@$(ECHO) $1"\n================ $2 ================\n"$(END_COLOUR)
endef

define normitest
	@$(ECHO) $(BLUE)"Test norminette..."$(END_COLOUR)
	@if norminette $(SRC_DIR) $(HEADER) $(LIBFT_SRC_FULL) | grep Error; then \
		$(ECHO) $(RED)"\n================ Norminette KO ================"$(END_COLOUR); \
	else \
		$(ECHO) $(GREEN)"\n================ Norminette OK ================"$(END_COLOUR); \
	fi
endef

define gitignore_gen
	@if test .gitignore ; then\
		$(ECHO) "*.o\n$(NAME)" > .gitignore; \
	fi ;
endef

.PHONY: all clean fclean re debug run bonus

all : $(MINILIBX)
	$(call normitest)
	$(call prompt,$(BLUE),"Creating $(NAME)")
	$(MAKE) $(NAME)

bonus : $(MINILIBX)
	$(call prompt,$(BLUE),"Creating $(NAME_BONUS)")
	
	$(MAKE) $(NAME_BONUS) CFLAGS="$(CFLAGS) -DBONUS -DHEIGHT=$(RAYCAST_HEIGHT) -DWIDTH=$(RAYCAST_WIDTH)"

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c Makefile $(HEADER)
	$(call percent)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo -n $(END_COLOUR)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ_MANDATORY) $(OBJ_COMMON)
	$(call percent)
	$(CC) $(CFLAGS) -o $@ $(OBJ_MANDATORY) $(INCLUDE)
	@echo -n $(END_COLOUR)
	$(call prompt,$(GREEN),"$(NAME) compiled")

$(NAME_BONUS) : $(LIBFT) $(OBJ_DIR) $(OBJ_COMMON) $(OBJ_DIR_BONUS) $(OBJ_BONUS) $(OBJ_MANDATORY) ./headers/bonus.h
	$(call percent)
	$(CC) $(CFLAGS) -o $@ $(OBJ_BONUS) $(INCLUDE)
	@echo -n $(END_COLOUR)
	$(call prompt,$(GREEN),"$(NAME_BONUS) compiled")

$(LIBFT) : $(LIBFT_SRC_FULL) libft/libft.h
	$(MAKE) libft.a -C libft

$(MINILIBX) :
	$(MAKE) -C minilibx-linux

$(OBJ_DIR):
	@mkdir -p $(sort $(dir ${OBJ_COMMON}))

$(OBJ_DIR_BONUS) : $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_BONUS)

clean :
	@$(ECHO) $(BLUE)Cleaning...$(END_COLOUR)
	@$(MAKE) fclean -C libft
	@$(MAKE) clean -C minilibx-linux
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)
	$(call prompt,$(GREEN),"$(NAME) cleared")

re :
	$(MAKE) fclean
	$(MAKE) all

run :
	$(MAKE) all
	@./$(NAME) map/42.cub

debug :
	$(MAKE) libft.a -C libft CFLAG="$(CFLAG) -g3"
	$(MAKE) re CFLAG="$(CFLAG) -g3"

MAKE = @make --no-print-directory
ECHO = echo

CC = cc
IFLAGS = -Iheaders/
CFLAGS = -Werror -Wall -Wextra -O2
CPPFLAGS = -DHEIGHT_WIN=$(SCREEN_HEIGHT) -DWIDTH_WIN=$(SCREEN_WIDTH)
ALLFLAGS = $(CFLAGS) $(IFLAGS) $(CPPFLAGS)
NAME = cub3D
NAME_BONUS = $(NAME)_bonus
HEADER = ./headers/cub3d.h ./headers/parsing.h ./headers/types.h
SRC_DIR=src/

SRC_LIST_COMMON:= init.c keyboard.c casting_utils.c main.c sprite.c draw_utils.c
SRC_LIST_MANDATORY:= frame_update.c raycast.c draw.c
SRC_LIST_P:= parse_keys.c parse_map.c parse_color.c parsing.c parse_keys_utils.c setup_map.c parse_map_utils.c parsing_utils.c inits_textures.c valide_key.c parse_map_v2.c
SRC_LIST_BONUS:= upscaling_bonus.c map_autotile_bonus.c map_autotile_utils_bonus.c miscellaneous_bonus.c mouse_bonus.c draw_bonus.c floor_ceilling_ray_bonus.c frame_update_bonus.c raycast_bonus.c map_gen_bonus.c map_inits_bonus.c animation_bonus.c

SRC_COMMON=$(addprefix $(SRC_DIR),$(SRC_LIST_COMMON)) $(addprefix $(SRC_DIR)parsing/,$(SRC_LIST_P))
SRC_MANDATORY= $(addprefix $(SRC_DIR),$(SRC_LIST_MANDATORY)) $(SRC_COMMON)
SRC_BONUS= $(addprefix $(SRC_DIR)bonus/,$(SRC_LIST_BONUS)) $(SRC_COMMON)

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

NB_FILES=$(words $(OBJ_MANDATORY))

#NB_OBJ = $(words $(wildcard obj/*.o obj/parsing/*.o obj/bonus/*.o))

SCREEN_HEIGHT := $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2))
SCREEN_WIDTH := $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1))

RAYCAST_HEIGHT := $(shell expr $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f2)) / 2)
RAYCAST_WIDTH := $(shell expr $(firstword $(shell xrandr --current | grep '*' | uniq | awk '{print $1}' | cut -d 'x' -f1)) / 2)

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

define percent
	@echo -n $(BLUE)"[$$(echo "scale=2; $$(find $(OBJ_DIR) -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%]" $(GREEN)
endef

define prompt
	@$(ECHO) $1"\n================ $2 ================\n"$(END_COLOUR)
endef

define normitest
	@$(ECHO) $(BLUE)"Test norminette..."$(END_COLOUR)
	@if norminette $(SRC_DIR) $(HEADER) $(LIBFT_DIR) | grep Error; then \
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
ifneq ("$(wildcard ${NAME_BONUS})", "")
	@rm -rf $(OBJ_COMMON) $(OBJ_BONUS) $(NAME_BONUS)
endif
	$(MAKE) $(NAME)

bonus : $(MINILIBX)
	$(call prompt,$(BLUE),"Creating $(NAME_BONUS)")
ifneq ("$(wildcard ${NAME})", "")
	@rm -rf $(OBJ_COMMON) $(OBJ_MANDATORY) $(NAME)
endif
	$(MAKE) $(NAME_BONUS) NB_FILES=$(words $(SRC_BONUS)) CPPFLAGS="$(CPPFLAGS) -DBONUS -DHEIGHT=$(RAYCAST_HEIGHT) -DWIDTH=$(RAYCAST_WIDTH)"

$(OBJ_DIR)%.o:  $(SRC_DIR)%.c Makefile $(HEADER)
	$(call percent)
	$(CC) $(ALLFLAGS) -c $< -o $@
	@echo -n $(END_COLOUR)

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ_MANDATORY) $(OBJ_COMMON)
	$(call percent)
	$(CC) $(ALLFLAGS) -o $@ $(OBJ_MANDATORY) $(INCLUDE)
	@echo -n $(END_COLOUR)
	$(call prompt,$(GREEN),"$(NAME) compiled")

$(NAME_BONUS) : $(LIBFT) $(OBJ_DIR) $(OBJ_COMMON) $(OBJ_DIR_BONUS) $(OBJ_BONUS) $(OBJ_MANDATORY) ./headers/bonus.h
	$(call percent)
	$(CC) $(ALLFLAGS) -o $@ $(OBJ_BONUS) $(INCLUDE)
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
	$(MAKE) re -C libft CFLAGS="$(CFLAGS) -g3"
	$(MAKE) re CFLAGS="$(CFLAGS) -g3"

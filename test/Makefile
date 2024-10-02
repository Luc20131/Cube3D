	MAKE = @make --no-print-directory

CC = cc
FLAG =
NAME = test

HEADER = ./headers/$(NAME).h
SRC_DIR=src/
SRC_LIST= testo.c
SRC=$(addprefix $(SRC_DIR),$(SRC_LIST))
OBJ_DIR=obj/
OBJ=$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

INCLUDE = -Lminilibx-linux -lmlx_Linux -lX11 -lXext -lm

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
	@echo $(BLUE)"Test norminette..."$(END_COLOUR)
	@if norminette $(SRC_LIST) $(HEADER) $(LIBFT_SRC_FULL) | grep Error; then \
		echo $(RED)"\n================ Norminette KO ================"$(END_COLOUR); \
	else \
		echo $(GREEN)"\n================ Norminette OK ================"$(END_COLOUR); \
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

$(OBJ_DIR)%.o: $(SRC_DIR)%.c Makefile $(HEADER)
	$(call percent)
	$(CC) $(FLAG) -c $< -o $@
	@echo -n $(END_COLOUR)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(call percent)
	$(CC) $(FLAG) -o $@ $(OBJ) $(INCLUDE)
	@echo -n $(END_COLOUR)
	$(call prompt,$(GREEN),"$(NAME) compiled")

$(LIBFT) : $(LIBFT_SRC_FULL) libft/libft.h
	$(MAKE) libft.a -C libft

$(OBJ_DIR):
	@mkdir $@

clean :
	@echo -e $(BLUE)Cleaning...$(END_COLOUR)
	@$(MAKE) fclean -C libft
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)
	$(call prompt,$(GREEN),"$(NAME) cleared")

re :
	$(MAKE) fclean
	$(MAKE) all

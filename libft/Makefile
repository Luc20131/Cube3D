CC = cc
CFLAGS = -Werror -Wall -Wextra
NAME = libft.a
SRC = ft_striteri.c ft_strmapi.c ft_strtrim.c ft_split.c ft_itoa.c ft_strjoin.c ft_substr.c ft_strnstr.c ft_memcmp.c ft_strlcpy.c ft_strlcat.c ft_putnbr_fd.c ft_putendl_fd.c ft_putstr_fd.c ft_putchar_fd.c ft_calloc.c ft_strdup.c ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c get_next_line/get_next_line.c ft_printf/ft_printf.c ft_printf/ft_put.c ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_free_splited.c
BONUS = ft_lstmap_bonus.c ft_lstiter_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstsize_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c
NB_FILES=$(words $(SRC))
OBJ = $(SRC:.c=.o)
OBJBONUS = $(BONUS:.c=.o)
OBJ_DIR=.
GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[0;34m"
END_COLOUR="\033[0m"

.PHONY: all clean fclean re bonus

define percent
	@echo -n $(BLUE)"[$$(echo "scale=2; $$(find $(OBJ_DIR) -name '*.o' | wc -l) / $(NB_FILES) * 100" | bc)%] " $(GREEN)
endef

$(NAME) : $(OBJ) libft.h
	$(call percent)
	ar -rc $@ $(OBJ)
	@echo $(GREEN)"\n================ libft compiled ================\n"$(END_COLOUR)

all : $(NAME)

clean :
	rm -f $(OBJ) $(OBJBONUS)

fclean : clean
	rm -f $(NAME)

%.o : %.c libft.h ft_printf/ft_printf.h get_next_line/get_next_line.h
	$(call percent)
	$(CC) $(CFLAGS) -c $< -o $@ -I.

re :
	$(MAKE) fclean
	$(MAKE) all

bonus : $(OBJ) $(OBJBONUS)
	$(MAKE) SRC="$(OBJ) $(OBJBONUS)"

debug :
	$(MAKE) re CFLAGS="$(CFLAGS) -g3"

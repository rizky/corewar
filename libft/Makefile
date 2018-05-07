# ==== Editable ====
NAME:= libft.a

FTAPATH:= ft_array/
FTA:= fta_alloc fta_append fta_new fta_reserve fta_resize fta_trim \
	fta_popback fta_popindex fta_clear fta_string fta_replace \
	fta_swap fta_overwrite fta_printdata

FTPFPATH:= ft_printf/
FTPF:= ft_printf ft_vprintf ft_vasprintf ft_convert \
		ft_convert_numeric_1 ft_convert_numeric_2 ft_convert_numeric_3 \
		ft_convert_char \
		ft_convert_double_1 ft_convert_double_2 ft_convert_double_3 \
		ft_convert_color \
		ft_convert_date \
		ft_convert_data ft_convert_memory

FTLSTPATH:= ft_lst/
FTLST:= ft_lstdel ft_lstmerge ft_lstswap ft_lstdelone ft_lstnew ft_lstfind ft_lstremoveif \
		ft_lstadd ft_lstiter ft_lstrev ft_lstaddlast ft_lstlast ft_lstsize ft_lstclear ft_lstmap \
		ft_lstsort ft_strsplit_tolst ft_putlst

FTMATHPATH:= ft_math/
FTMATH:= ft_round_base ft_modf

FTMEMPATH:= ft_mem/
FTMEM:= ft_memdel ft_memalloc ft_memmove ft_memccpy ft_memset ft_memchr ft_memcmp ft_memcpy ft_bzero

FTSTRPATH:= ft_str/
FTSTR:= ft_strchr ft_strequ ft_strmap ft_strnew ft_strsub ft_strclr ft_striter ft_strmapi ft_strnstr ft_strtrim \
		ft_strcmp ft_striteri ft_strncat ft_strrchr ft_putstr ft_strcpy ft_strjoin ft_strncmp ft_strsplit \
		ft_putstr_fd ft_strdel ft_strlcat ft_strncpy ft_strcat ft_strdup ft_strlen ft_strnequ ft_strstr \
		ft_putendl_fd ft_itoa ft_putnbr_fd ft_putchar ft_putchar_fd ft_putendl ft_isdigit  ft_ishexdigit \
		ft_isdigit  ft_ishexdigit ft_atoi ft_isprint ft_putnbr ft_tolower ft_isalnum   ft_toupper ft_isalpha \
		ft_isascii

FTWCHARPATH:= ft_wchar/
FTWCHAR:= wide_char

FTREPATH:= ft_re/
FTRE:= ft_re ft_re_match_1 ft_re_match_2 ft_re_match_3 ft_re_match_4

FILES:= ft_date get_next_line

# ==================

# ==== Standard ====
CC:=clang
CCHPATH:=obj/
SRCPATH:=src/
HDRPATH:=include/
CFLAGS:=-Wall -Wextra -Werror -I $(HDRPATH)
# ==================

# ===== Colors =====
END:="\033[0;0m"
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;35m"
PURPLE:="\033[1;36m"
WHITE:="\033[1;37m"
# ==================

# ====== Auto ======
FILES+=$(addprefix $(FTAPATH),$(FTA))
FILES+=$(addprefix $(FTLSTPATH),$(FTLST))
FILES+=$(addprefix $(FTMATHPATH),$(FTMATH))
FILES+=$(addprefix $(FTMEMPATH),$(FTMEM))
FILES+=$(addprefix $(FTSTRPATH),$(FTSTR))
FILES+=$(addprefix $(FTWCHARPATH),$(FTWCHAR))
FILES+=$(addprefix $(FTPFPATH),$(FTPF))
FILES+=$(addprefix $(FTREPATH),$(FTRE))

SRC:=$(addprefix $(SRCPATH),$(addsuffix .c,$(FILES)))
OBJ:=$(addprefix $(CCHPATH),$(addsuffix .o,$(FILES)))
# ==================
CCHF:=.cache_exists

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(END)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(GREEN) " - Done" $(END)

$(CCHPATH)%.o: $(SRCPATH)%.c | $(CCHF)
	@echo ".\c"
	@$(CC) $(CFLAGS) -c $< -o $@

%.c:
	@echo $(RED) "Missing file : $@"

$(CCHF):
	@mkdir $(CCHPATH)
	@mkdir $(CCHPATH)$(FTAPATH)
	@mkdir $(CCHPATH)$(FTPFPATH)
	@mkdir $(CCHPATH)$(FTLSTPATH)
	@mkdir $(CCHPATH)$(FTMATHPATH)
	@mkdir $(CCHPATH)$(FTMEMPATH)
	@mkdir $(CCHPATH)$(FTSTRPATH)
	@mkdir $(CCHPATH)$(FTWCHARPATH)
	@mkdir $(CCHPATH)$(FTREPATH)
	@touch $(CCHF)

clean:
	@rm -rf $(CCHPATH)
	@rm -f $(CCHF)

fclean: clean
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

norm:
	@echo $(RED)
	@norminette $(SRC) $(HDRPATH) | grep -v Norme -B1 || true
	@echo $(END)

.PHONY: all clean fclean re test norme

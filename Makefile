NAME		= minishell

SRCS_DIR	= srcs
OBJS_DIR	= objs
INC_DIR		= includes

SRCS		= main.c		\

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

DEPS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))


CPPFLAGS	= -I$(INC_DIR) -MD -MP
CFLAGS		= -Wall -Wextra -Werror -fPIE
CC			= cc

LIBFT_DIR	= Libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= $(LIBFT_DIR)
LDFLAGS		+= -L$(LIBFT_DIR)
LDLIBS		+= -lft
CPPFLAGS	+= -I$(LIBFT_INC)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(OBJS): | $(OBJS_DIR)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(LIBFT_LIB): $(LIBFT_LIB)@build
.PHONY: $(LIBFT_LIB)@build
$(LIBFT_LIB)@build:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: 
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY : all clean fclean re

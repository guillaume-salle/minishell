NAME		= minishell

SRCS_DIR	= srcs
OBJS_DIR	= objs
INC_DIR		= includes

SRCS		= main.c	
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

CPPFLAGS	= -I$(INC_DIR) -MD -MP
CFLAGS		= -Wall -Wextra -Werror -fPIE
CC			= cc $(CPPFLAGS) $(CFLAGS)

LIBFT_DIR	= Libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= $(LIBFT_DIR)/includes
LDFLAGS		+= -L$(LIBFT_DIR)
LDLIBS		+= -lft
CPPFLAGS	+= -I$(LIBFT_INC)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)

# Create objs directory if does not exist
$(OBJS): | $(OBJS_DIR)
$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(LIBFT_LIB): $(LIBFT_LIB)@build
.PHONY: $(LIBFT_LIB)@build
$(LIBFT_LIB)@build:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: 
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re

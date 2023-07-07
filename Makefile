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
LDLIBS		+= -lft
LDFLAGS		+= -L$(LIBFT_DIR)
CPPFLAGS	+= -I$(LIBFT_INC)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_LIB)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) $(LDLIBS)

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

# Tests
TESTS_DIR	= tests
# Libraries for framework Check
LDLIBS		+= -lcheck -lm -lrt -lpthread
TESTS		= echo.c
TESTS_OBJS	= $(addprefix $(TESTS_DIR)/, $(TESTS:.c=.o))
$(NAME).o: $(OBJS) $(LIBFT_LIB)
	$(CC) -c $(OBJS) -o $@
$(OBJS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) -c $< -o $@
tests: $(NAME).o $(TESTS_OBJS) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(NAME).o $(TESTS_OBJ) -o $@
test: tests
	./tests
.PHONY: test

-include $(DEPS)

.PHONY: all clean fclean re

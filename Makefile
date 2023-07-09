NAME		= minishell

SRCS_DIR	= src
OBJS_DIR	= obj
INC_DIR		= includes

SRCS		= main.c	\
			  run_command.c
OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))
SRCS	 	:= $(addprefix $(SRCS_DIR)/, $(SRCS))

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

fclean::
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# Tests
TESTS_DIR	= tests
TESTS_SRCS	= main.c	\
			  test_echo.c
TESTS		= $(addprefix $(TESTS_DIR)/, $(TESTS_SRCS))
TESTS		+= $(filter-out $(SRCS_DIR)/main.c, $(SRCS))
test.exe: $(TESTS)
	cc -Iincludes $^ -o $@ $(LDFLAGS) $(LDLIBS) -lcheck -lm -lrt -lsubunit -lpthread
check: test.exe 
	chmod +x ./test.exe
	./test.exe
fclean::
	rm -f test.exe
.PHONY: check 

-include $(DEPS)

.PHONY: all clean fclean re

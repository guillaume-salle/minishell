NAME		= minishell

SRCS_DIR	= src
OBJS_DIR	= obj
INC_DIR		= includes

SRCS		= main.c	\
			  utils_env.c free.c signal_handlers.c handle_history.c	\
			  path.c envp.c	\
			  builtins/echo.c builtins/env.c builtins/cd.c	\
			  builtins/pwd.c builtins/export.c builtins/unset.c	\
			  execution/exec_command_list.c	execution/exec_partition.c		\
			  execution/exec_word.c execution/redirections.c
OBJS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
DEPS		:= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))
SRCS	 	:= $(addprefix $(SRCS_DIR)/, $(SRCS))

CPPFLAGS	= -I$(INC_DIR) -MD -MP
CFLAGS		= -Wall -Wextra -Werror -fPIE
CC			= cc $(CPPFLAGS) $(CFLAGS)

LIBFT_DIR	= Libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a
LIBFT_INC	= $(LIBFT_DIR)/includes
LDLIBS		+= -lft -lreadline
LDFLAGS		+= -L$(LIBFT_DIR)
CPPFLAGS	+= -I$(LIBFT_INC)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
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
TESTS_SRCS	= utils.c\
			  test_echo.c test_env.c test_cd.c test_pwd.c	\
			  test_export.c test_unset.c	\
			  test_exec_word.c
TESTS		= $(addprefix $(TESTS_DIR)/, $(TESTS_SRCS))

check.exe: $(TESTS_DIR)/main.c $(filter-out $(SRCS_DIR)/main.c, $(SRCS)) $(TESTS) $(LIBFT_LIB)
	cc $(CPPFLAGS) -fPIE -Itests $^ -o $@ $(LDFLAGS) $(LDLIBS) -lcheck -lm -lrt -lsubunit -lpthread
check: check.exe 
	chmod +x ./check.exe
	./check.exe

test.exe: $(TESTS_DIR)/main2.c $(filter-out $(SRCS_DIR)/main.c, $(SRCS)) $(LIBFT_LIB)
	cc $(CPPFLAGS) -fPIE -Itests $^ -o $@ $(LDFLAGS) $(LDLIBS)
test: test.exe
	chmod +x ./test.exe

fclean::
	rm -f check.exe test.exe
	rm -f check.d test.d
.PHONY: check 

-include $(DEPS)

.PHONY: all clean fclean re

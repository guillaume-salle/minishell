#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

int redirect_fd_to_buffer(int fd);
ssize_t restore_fd_and_read_buffer(int fd, char* buffer, size_t size);
t_list2* new_node(char* name, char* content);

Suite* echo_suite(void);
Suite* env_suite(void);
Suite* cd_suite(void);

#endif // TEST_H

#ifndef TESTS_H
#define TESTS_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"

int redirect_stdout_to_buffer();
ssize_t restore_stdout_and_read_buffer(char* buffer, size_t size);
t_list2* new_node(char* name, char* content);
void add_node(t_list2** head, char* name, char* content);

Suite* echo_suite(void);
Suite* env_suite(void);
Suite* cd_suite(void);

#endif // TEST_H

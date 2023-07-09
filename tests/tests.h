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

Suite	*add_suite_echo(void);

#endif // TEST_H

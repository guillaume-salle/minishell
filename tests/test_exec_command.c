#include "tests.h"

extern t_vars g_vars;

#include <check.h>

void run_test_cmd(char* cmd[], char* expected_output) {
    if (redirect_fd_to_buffer(STDOUT_FILENO) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

    char buffer[1024];
    ssize_t len = restore_fd_and_read_buffer(STDOUT_FILENO, buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    ck_assert_msg(strcmp(buffer, expected_output) == 0,
			"Expected output was '%s', but actual output was '%s'",
			expected_output, buffer);
}

START_TEST(test_exec_builtin_echo) {
    t_vars vars;
    // Assuming that initializing 'vars' isn't necessary for this test
    // If necessary, initialize 'vars' here

    int result = my_execvp((char *[]){"echo", "test_echo", NULL}, &vars);
    ck_assert_int_eq(result, 0);  // Assuming '0' means success in your builtins
}
END_TEST

Suite* execute_command_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Command");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_exec_builtin_echo);
    
    suite_add_tcase(s, tc_core);

    return s;
}

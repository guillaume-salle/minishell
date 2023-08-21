#include "tests.h"

extern t_vars g_vars;

#include <check.h>

void run_test_cmd(t_commande *cmd, char* expected_output, t_vars vars) {
    if (redirect_fd_to_buffer(STDOUT_FILENO) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

	exec_command(cmd, vars);

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
	t_commande cmd;

	char* test_strings[] = {"echo", "Hello,", "World!", NULL};
	cmd->cmds_split = test_strings;
	cmd->id = WORD;
	char* expected_output = "Hello, World!\n";

	run_test_cmd(test_strings, expected_output, vars);
}
END_TEST

START_TEST(test_exec_builtin_echo_2) {
    t_vars vars;

	char* test_strings[] = {"echo", "-s", "Hello,", "World!", NULL};
	cmd->cmds_split = test_strings;
	cmd->id = WORD;
	char* expected_output = "-s Hello, World!\n";

	run_test_cmd(test_strings, expected_output, vars);
}
END_TEST

Suite* execute_command_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Command");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_exec_builtin_echo);
    tcase_add_test(tc_core, test_exec_builtin_echo_2);
    
    suite_add_tcase(s, tc_core);

    return s;
}

#include "tests.h"

extern t_vars g_vars;

void run_test_cmd(t_commande *cmd, char* expected_output, t_vars *vars,
		int fd) {
    if (redirect_fd_to_buffer(fd) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

	exec_command(cmd, vars);
	if (strlen(expected_output) == 0)
		write(fd, "\0", 1);

    char buffer[1024];
    ssize_t len = restore_fd_and_read_buffer(fd, buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    ck_assert_msg(strcmp(buffer, expected_output) == 0,
			"Expected output was '%s', but actual output was '%s'",
			expected_output, buffer);
}

START_TEST(test_exec_builtin_echo_1) {
    t_vars vars;
	t_commande cmd;

	char* test_strings[] = {"echo", "Hello,", "World!", NULL};
	cmd.cmds_split = test_strings;
	cmd.id = WORD;
	char* expected_output = "Hello, World!\n";

	run_test_cmd(&cmd, expected_output, &vars, STDOUT_FILENO);
}
END_TEST

START_TEST(test_exec_builtin_echo_2) {
    t_vars vars;
	t_commande cmd;

	char* test_strings[] = {"echo", "-s", "Hello,", "World!", NULL};
	cmd.cmds_split = test_strings;
	cmd.id = WORD;
	char* expected_output = "-s Hello, World!\n";

	run_test_cmd(&cmd, expected_output, &vars, STDOUT_FILENO);
}
END_TEST

START_TEST(test_exec_builtin_cd_1) {
	t_commande cmd;

	char *new_dir = "/usr";
	char* test_strings[] = {"cd", new_dir, NULL};
	cmd.cmds_split = test_strings;
	cmd.id = WORD;
	cmd.argc = 2;
	char* expected_output = "";

	run_test_cmd(&cmd, expected_output, &g_vars, STDOUT_FILENO);

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    ck_assert_str_eq(cwd, new_dir);
}
END_TEST

START_TEST (test_exec_builtin_cd_2) {
	t_commande cmd;

    char *new_dir = "/nonexistentdirectory";
    char buffer[1024];


	char* test_strings[] = {"cd", new_dir, NULL};
	cmd.cmds_split = test_strings;
	cmd.id = WORD;
	cmd.argc = 2;
	char* expected_output = "cd: No such file or directory\n";

	run_test_cmd(&cmd, expected_output, &g_vars, STDERR_FILENO);
}
END_TEST

Suite* execute_command_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Command");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_exec_builtin_echo_1);
    tcase_add_test(tc_core, test_exec_builtin_echo_2);
    tcase_add_test(tc_core, test_exec_builtin_cd_1);
    tcase_add_test(tc_core, test_exec_builtin_cd_2);
    
    suite_add_tcase(s, tc_core);

    return s;
}

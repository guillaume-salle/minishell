#include "tests.h"

void run_test_pwd() {
    char expected_cwd[1024];
    if (getcwd(expected_cwd, sizeof(expected_cwd)) == NULL) {
        ck_abort_msg("Failed to get current working directory");
    }

    if (redirect_fd_to_buffer(STDOUT_FILENO) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

    int ret = pwd(0, NULL, NULL);
    ck_assert_msg(ret == 0, "pwd function failed");
	
    char buffer[1024];
    ssize_t len = restore_fd_and_read_buffer(STDOUT_FILENO, buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    // Add a newline to the expected output since ft_putendl_fd adds one
	char expected_output[strlen(expected_cwd) + 2];
    snprintf(expected_output, sizeof(expected_output), "%s\n", expected_cwd);

    ck_assert_msg(strcmp(buffer, expected_output) == 0,
            "Expected current directory was '%s', but actual was '%s'",
            expected_output, buffer);
}

START_TEST(test_pwd_1) {
    run_test_pwd();
} END_TEST

Suite* pwd_suite() {
    Suite* s = suite_create("pwd");
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_pwd_1);
    // Add more tests as needed

    suite_add_tcase(s, tc_core);
    return s;
}

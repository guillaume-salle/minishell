#include "tests.h"

extern t_global	g_vars;

START_TEST (test_cd_change_to_valid_directory)
{
    char *new_dir = "/usr";
    int result = cd(2, (char *[]){"cd", new_dir, NULL});
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    ck_assert_int_eq(result, 0);
    ck_assert_str_eq(cwd, new_dir);
}
END_TEST

START_TEST (test_cd_change_to_invalid_directory)
{
    char *new_dir = "/nonexistentdirectory";
    char buffer[1024];

    // Redirect stderr to a buffer
    redirect_fd_to_buffer(STDERR_FILENO);

    int result = cd(2, (char *[]){"cd", new_dir, NULL});

    // Restore stderr and read the content of the buffer
    ssize_t len = restore_fd_and_read_buffer(STDERR_FILENO, buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to read buffer");
    }

    ck_assert_int_ne(result, 0);
    ck_assert_str_eq(buffer, "cd: No such file or directory\n");
}
END_TEST

Suite* cd_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("cd");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_cd_change_to_valid_directory);
    tcase_add_test(tc_core, test_cd_change_to_invalid_directory);
    suite_add_tcase(s, tc_core);

    return s;
}

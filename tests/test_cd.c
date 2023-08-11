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

START_TEST (test_cd_update_PWD_and_OLDPWD)
{
    char *initial_dir = "/usr";
    char *new_dir = "/tmp";

    // Change to initial directory
    int ret_val = cd(2, (char *[]){"cd", initial_dir, NULL});
    ck_assert_int_eq(ret_val, 0); // Check that the return value is 0

    // Manually update PWD and OLDPWD for the test
	char *expected_oldpwd = "expected_oldpwd";
    my_putenv("PWD", expected_oldpwd);
    my_putenv("OLDPWD", "whatever");

    // Change to new directory
    ret_val = cd(2, (char *[]){"cd", new_dir, NULL});
    ck_assert_int_eq(ret_val, 0); // Check that the return value is 0

    char *pwd = my_getenv("PWD");
    char *oldpwd = my_getenv("OLDPWD");

    // Check that PWD is updated to the new directory
    ck_assert_str_eq(pwd, new_dir);

    // Check that OLDPWD is updated to the initial directory
    ck_assert_str_eq(oldpwd, expected_oldpwd);
}
END_TEST

Suite* cd_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("cd");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_cd_change_to_valid_directory);
    tcase_add_test(tc_core, test_cd_change_to_invalid_directory);
	tcase_add_test(tc_core, test_cd_update_PWD_and_OLDPWD);
    suite_add_tcase(s, tc_core);

    return s;
}

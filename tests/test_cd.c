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
    char *new_dir = "/bin";
    
    // Change to initial directory and update PWD and OLDPWD
    cd(2, (char *[]){"cd", initial_dir, NULL});
    my_putenv("PWD", initial_dir);
    my_putenv("OLDPWD", initial_dir);

    // Change to new directory
    cd(2, (char *[]){"cd", new_dir, NULL});

    char *pwd = NULL;
    char *oldpwd = NULL;

    t_list2* current = g_vars.envp_list;
    while (current) {
        if (strcmp(current->name, "PWD") == 0) {
            pwd = current->content;
        }
        if (strcmp(current->name, "OLDPWD") == 0) {
            oldpwd = current->content;
        }
        current = current->next;
    }

	printf("PWD: %s\n", pwd);      // Debugging print
    printf("OLDPWD: %s\n", oldpwd); // Debugging print

	printf("PWD: %s\n", getenv("PWD"));      // Debugging print
    printf("OLDPWD: %s\n", getenv("OLDPWD")); // Debugging print

    // Check that PWD is updated to the new directory
    ck_assert_str_eq(pwd, new_dir);

    // Check that OLDPWD is updated to the initial directory
    ck_assert_str_eq(oldpwd, initial_dir);
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

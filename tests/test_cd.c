#include "tests.h"

extern t_global	g_vars;

START_TEST (test_cd_change_to_valid_directory)
{
    char *new_dir = "/usr";
    int result = my_cd(2, (char *[]){"cd", new_dir, NULL}, g_vars.envp_list);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    ck_assert_int_eq(result, 0);
    ck_assert_str_eq(cwd, new_dir);
}
END_TEST

START_TEST (test_cd_change_to_invalid_directory)
{
    char *new_dir = "/nonexistentdirectory";
    int result = my_cd(2, (char *[]){"cd", new_dir, NULL}, g_vars.envp_list);
    ck_assert_int_ne(result, 0);
}
END_TEST

START_TEST (test_cd_no_arguments_go_home)
{
    char *home_dir = my_getenv("HOME");
    int result = my_cd(1, (char *[]){"cd", NULL}, g_vars.envp_list);
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    ck_assert_int_eq(result, 0);
    ck_assert_str_eq(cwd, home_dir);
}
END_TEST

Suite* cd_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("cd");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_cd_change_to_valid_directory);
    tcase_add_test(tc_core, test_cd_change_to_invalid_directory);
    tcase_add_test(tc_core, test_cd_no_arguments_go_home);
    suite_add_tcase(s, tc_core);

    return s;
}

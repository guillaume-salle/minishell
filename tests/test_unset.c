#include "tests.h"

START_TEST(test_unset_single_variable) {
    t_vars vars;
    vars.envp_list = NULL;
    my_putenv("key", "value", &vars); // Assume you have a function to add an environment variable

    unset(2, (char *[]){"unset", "key"}, &vars);
    ck_assert_ptr_eq(my_getenv("key", &vars), NULL); // Assume you have a function to retrieve an environment variable
}
END_TEST

START_TEST(test_unset_multiple_variables) {
    t_vars vars;
    vars.envp_list = NULL;
    my_putenv("key1", "value1", &vars);
    my_putenv("key2", "value2", &vars);

    unset(3, (char *[]){"unset", "key1", "key2"}, &vars);
    ck_assert_ptr_eq(my_getenv("key1", &vars), NULL);
    ck_assert_ptr_eq(my_getenv("key2", &vars), NULL);
}
END_TEST

START_TEST(test_unset_nonexistent_variable) {
    t_vars vars;
    vars.envp_list = NULL;

    unset(2, (char *[]){"unset", "key"}, &vars);
    ck_assert_ptr_eq(my_getenv("key", &vars), NULL);
}
END_TEST

Suite* unset_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("unset");

    // Core test case
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_unset_single_variable);
    tcase_add_test(tc_core, test_unset_multiple_variables);
    tcase_add_test(tc_core, test_unset_nonexistent_variable);
    suite_add_tcase(s, tc_core);

    return s;
}


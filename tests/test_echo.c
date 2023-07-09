#include <check.h>
#include <stdlib.h>
#include "minishell.h"

START_TEST (test_echo)
{
    // The echo command should return the string passed to it
    char *output = run_command("echo hello");
    ck_assert_str_eq(output, "hello\n");
}
END_TEST

Suite *add_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("test echo");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_echo);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = add_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include <check.h>
#include <stdlib.h>
#include "minishell.h"
#include "tests.h"

START_TEST (test_echo)
{
    // The echo command should return the string passed to it
    char *output = run_command("echo hello");
    ck_assert_str_eq(output, "hello\n");
}
END_TEST

Suite *add_suite_echo(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("test echo");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_echo);
    suite_add_tcase(s, tc_core);

    return s;
}

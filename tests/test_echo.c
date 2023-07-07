#include <check.h>
#include "minishell.h"

START_TEST (test_echo)
{
    // The echo command should return the string passed to it
    char *output = run_command("echo hello");
    ck_assert_str_eq(output, "hello\n");
}
END_TEST


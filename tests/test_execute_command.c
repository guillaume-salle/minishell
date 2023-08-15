#include "tests.h"

extern t_vars g_vars;

#include <check.h>

// ... [Other includes, e.g., your minishell header]

START_TEST(test_is_builtin) {
    ck_assert_int_eq(is_builtin("cd"), 1);
    ck_assert_int_eq(is_builtin("echo"), 1);
    ck_assert_int_eq(is_builtin("pwd"), 1);
    ck_assert_int_eq(is_builtin("ls"), 0);  // 'ls' isn't a built-in
    ck_assert_int_eq(is_builtin("randomcmd"), 0);  // Random command name
}
END_TEST

START_TEST(test_exec_builtin_echo) {
    t_vars vars;
    // Assuming that initializing 'vars' isn't necessary for this test
    // If necessary, initialize 'vars' here

    int result = exec_builtin(2, (char *[]){"echo", "test_echo"}, &vars);
    ck_assert_int_eq(result, 0);  // Assuming '0' means success in your builtins
}
END_TEST

START_TEST(test_exec_builtin_invalid) {
    t_vars vars;
    // Again, assuming 'vars' initialization isn't needed here

    int result = exec_builtin(1, (char *[]){"invalidcmd"}, &vars);
    // Expecting some error code here for an invalid command, let's assume '-1' for simplicity
    ck_assert_int_eq(result, -1);
}
END_TEST

// For 'execute_command', it's a bit trickier since it involves forking.
// An integration test where you run the minishell and execute actual commands
// might be more suited to test its full functionality. Here, we can just 
// make a basic test.

START_TEST(test_execute_command_builtin) {
    t_commande cmd;
    cmd.cmds_split = (char *[]){"echo", "test_execute_command"};
    cmd.argc = 2;
    t_vars vars;
    // Initialize 'vars' if needed

    // Redirect stdout to a buffer, so we can check the output

    char buffer[128];
    int old_stdout = dup(1);
    FILE* new_stdout = fmemopen(buffer, 128, "w");
    dup2(fileno(new_stdout), 1);

    execute_command(&cmd, &vars);

    fflush(new_stdout);
    fclose(new_stdout);
    dup2(old_stdout, 1);
    close(old_stdout);

    ck_assert_str_eq(buffer, "test_execute_command\n");  // Assuming echo appends a newline
}
END_TEST

Suite* execute_command_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Command");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_is_builtin);
    tcase_add_test(tc_core, test_exec_builtin_echo);
    tcase_add_test(tc_core, test_exec_builtin_invalid);
    tcase_add_test(tc_core, test_execute_command_builtin);
    
    suite_add_tcase(s, tc_core);

    return s;
}

#include "tests.h"

extern t_vars g_vars;

START_TEST(test_isValidVariableName)
{
    ck_assert_msg(is_valid_variable_name("varName"), "Failed on 'varName'");
    ck_assert_msg(is_valid_variable_name("_var_name"), "Failed on '_var_name'");
    ck_assert_msg(!is_valid_variable_name("123VAR"), "Failed on '123VAR'");
    ck_assert_msg(!is_valid_variable_name("var-name"), "Failed on 'var-name'");
}
END_TEST

START_TEST(test_export_new_variable) {
    t_vars local_vars;
    local_vars.envp_list = NULL; // Initialize other members of t_vars as needed

    int result = export(2, (char *[]){"export", "key=value"}, &local_vars);
    ck_assert_int_eq(result, 0);

    char *retrieved_value = my_getenv("key", &local_vars);
    ck_assert_msg(retrieved_value != NULL, "Failed to retrieve the value for 'key'");
    if (retrieved_value != NULL) {
        ck_assert_str_eq(retrieved_value, "value");
    }
}
END_TEST

START_TEST(test_export_multiple_variables) {
    t_vars local_vars;
    local_vars.envp_list = NULL; // Initialize other members of t_vars as needed

    int result = export(4, (char *[]){"export", "key1=value1", "key2=value2", "key3=value3"}, &local_vars);
    ck_assert_int_eq(result, 0);

    char *retrieved_value1 = my_getenv("key1", &local_vars);
    ck_assert_msg(retrieved_value1 != NULL, "Failed to retrieve the value for 'key1'");
    if (retrieved_value1 != NULL) {
        ck_assert_str_eq(retrieved_value1, "value1");
    }

    char *retrieved_value2 = my_getenv("key2", &local_vars);
    ck_assert_msg(retrieved_value2 != NULL, "Failed to retrieve the value for 'key2'");
    if (retrieved_value2 != NULL) {
        ck_assert_str_eq(retrieved_value2, "value2");
    }

    char *retrieved_value3 = my_getenv("key3", &local_vars);
    ck_assert_msg(retrieved_value3 != NULL, "Failed to retrieve the value for 'key3'");
    if (retrieved_value3 != NULL) {
        ck_assert_str_eq(retrieved_value3, "value3");
    }
}
END_TEST

START_TEST(test_export_change_same_variable) {
    t_vars local_vars;
    local_vars.envp_list = NULL; // Initialize other members of t_vars as needed

    // Initial assignment
    int result = export(2, (char *[]){"export", "key=value1"}, &local_vars);
    ck_assert_int_eq(result, 0);
    char *retrieved_value = my_getenv("key", &local_vars);
    ck_assert_msg(retrieved_value != NULL, "Failed to retrieve the value for 'key'");
    if (retrieved_value != NULL) {
        ck_assert_str_eq(retrieved_value, "value1");
    }

    // Change the value
    result = export(2, (char *[]){"export", "key=value2"}, &local_vars);
    ck_assert_int_eq(result, 0);
    retrieved_value = my_getenv("key", &local_vars);
    ck_assert_msg(retrieved_value != NULL, "Failed to retrieve the changed value for 'key'");
    if (retrieved_value != NULL) {
        ck_assert_str_eq(retrieved_value, "value2");
    }

    // Change the value again
    result = export(2, (char *[]){"export", "key=value3"}, &local_vars);
    ck_assert_int_eq(result, 0);
    retrieved_value = my_getenv("key", &local_vars);
    ck_assert_msg(retrieved_value != NULL, "Failed to retrieve the changed value for 'key'");
    if (retrieved_value != NULL) {
        ck_assert_str_eq(retrieved_value, "value3");
    }
}
END_TEST

Suite* export_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("export");

    // Core test case
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_isValidVariableName);
    tcase_add_test(tc_core, test_export_new_variable);
    tcase_add_test(tc_core, test_export_multiple_variables);
    tcase_add_test(tc_core, test_export_change_same_variable);
    suite_add_tcase(s, tc_core);

    return s;
}



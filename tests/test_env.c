#include "tests.h"

START_TEST(test_new_node) {
    t_list2* node = new_node("TEST", "VALUE");
    ck_assert_str_eq(node->name, "TEST");
    ck_assert_str_eq(node->content, "VALUE");
    ck_assert_ptr_eq(node->next, NULL);
    free(node->name);
    free(node->content);
    free(node);
} END_TEST

START_TEST(test_add_node) {
    t_list2* env = NULL;
    add_node(&env, "TEST1", "VALUE1");
    add_node(&env, "TEST2", "VALUE2");
    ck_assert_str_eq(env->name, "TEST1");
    ck_assert_str_eq(env->content, "VALUE1");
    ck_assert_str_eq(env->next->name, "TEST2");
    ck_assert_str_eq(env->next->content, "VALUE2");
    // Free the nodes after testing
    free(env->next->name);
    free(env->next->content);
    free(env->next);
    free(env->name);
    free(env->content);
    free(env);
} END_TEST

START_TEST(test_env) {
    // Prepare the environment
    t_list2* env_list = NULL;
    add_node(&env_list, "TEST1", "VALUE1");
    add_node(&env_list, "TEST2", "VALUE2");
    
    // Redirect stdout to a buffer
    if (redirect_stdout_to_buffer() == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

    // Call env
    env(env_list);

    // Read the buffer
    char buffer[128];
    ssize_t len = restore_stdout_and_read_buffer(buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    // Check the output
    char expected_output[] = "TEST1=VALUE1\nTEST2=VALUE2\n";
    ck_assert_msg(strcmp(buffer, expected_output) == 0, "Expected output was '%s', but actual output was '%s'", expected_output, buffer);

    // Free the nodes after testing
    free(env_list->next->name);
    free(env_list->next->content);
    free(env_list->next);
    free(env_list->name);
    free(env_list->content);
    free(env_list);
} END_TEST

Suite* env_suite(void) {
    Suite* s = suite_create("env");
    TCase* tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_new_node);
    tcase_add_test(tc_core, test_add_node);
    tcase_add_test(tc_core, test_env);

    suite_add_tcase(s, tc_core);

    return s;
}

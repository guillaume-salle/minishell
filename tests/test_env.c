#include "tests.h"

START_TEST(test_new_node) {
    t_list* node = new_node("TEST", "VALUE");
    ck_assert_str_eq(node->name, "TEST");
    ck_assert_str_eq(node->content, "VALUE");
    ck_assert_ptr_eq(node->next, NULL);
    free(node->name);
    free(node->content);
    free(node);
} END_TEST

START_TEST(test_add_node) {
    t_list* env_list = NULL;
    add_node(&env_list, "TEST1", "VALUE1");
    add_node(&env_list, "TEST2", "VALUE2");
    ck_assert_str_eq(env_list->name, "TEST2");
    ck_assert_str_eq(env_list->content, "VALUE2");
    ck_assert_str_eq(env_list->next->name, "TEST1");
    ck_assert_str_eq(env_list->next->content, "VALUE1");
    // Free the nodes after testing
    free(env_list->next->name);
    free(env_list->next->content);
    free(env_list->next);
    free(env_list->name);
    free(env_list->content);
    free(env_list);
} END_TEST

START_TEST(test_env_empty) {
    // Prepare an empty environment
    t_list* env_list = NULL;

    // Redirect stdout to a buffer
    if (redirect_fd_to_buffer(STDOUT_FILENO) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

    // Call env
    print_env(env_list);
    write(1, "\0", 1); // Write a null byte to the pipe to signal the end of the output

    // Read the buffer
    char buffer[128];
    ssize_t len = restore_fd_and_read_buffer(STDOUT_FILENO, buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    // Check the output
    char expected_output[] = "";
    ck_assert_msg(strcmp(buffer, expected_output) == 0, "Expected output was '%s', but actual output was '%s'", expected_output, buffer);
} END_TEST

START_TEST(test_env_single) {
    // Prepare the environment with a single entry
    t_list* env_list = NULL;
    add_node(&env_list, "SINGLE_TEST", "SINGLE_VALUE");

    // Redirect stdout to a buffer
    if (redirect_fd_to_buffer(STDOUT_FILENO) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

    // Call env
    print_env(env_list);

    // Read the buffer
    char buffer[128];
    ssize_t len = restore_fd_and_read_buffer(STDOUT_FILENO, buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    // Check the output
    char expected_output[] = "SINGLE_TEST=SINGLE_VALUE\n";
    ck_assert_msg(strcmp(buffer, expected_output) == 0, "Expected output was '%s', but actual output was '%s'", expected_output, buffer);

    // Free the node after testing
    free(env_list->name);
    free(env_list->content);
    free(env_list);
} END_TEST

START_TEST(test_env) {
    // Prepare the environment
    t_list* env_list = NULL;
    add_node(&env_list, "TEST1", "VALUE1");
    add_node(&env_list, "TEST2", "VALUE2");
    
    // Redirect stdout to a buffer
    if (redirect_fd_to_buffer(STDOUT_FILENO) == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

    // Call env
    print_env(env_list);

    // Read the buffer
    char buffer[128];
    ssize_t len = restore_fd_and_read_buffer(STDOUT_FILENO, buffer, sizeof(buffer));
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
    tcase_add_test(tc_core, test_env_empty);
    tcase_add_test(tc_core, test_env_single);

    suite_add_tcase(s, tc_core);

    return s;
}

#include "tests.h"

START_TEST(test_echo)
{
	char* test_strings[] = {"echo", "Hello,", "World!", NULL};

	if (redirect_stdout_to_buffer() == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

//    echo(test_strings);

    char buffer[128];
    ssize_t len = restore_stdout_and_read_buffer(buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

	char* expected_output = "Hello, World!\n";
    ck_assert_msg(strcmp(buffer, expected_output) == 0, "Output was '%s'", buffer);
}
END_TEST

Suite* echo_suite() {
    Suite* s = suite_create("echo");
    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_echo);
    suite_add_tcase(s, tc_core);
    return s;
}

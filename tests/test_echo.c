#include "tests.h"

void run_test_echo(char* test_strings[], char* expected_output) {
    if (redirect_stdout_to_buffer() == -1) {
        ck_abort_msg("Failed to redirect stdout to buffer");
    }

	int argc = 0;
	while (test_strings[argc] != NULL)
		argc++;
    echo(argc, test_strings);
	if (strlen(expected_output) == 0)
		write(1, "\0", 1);

    char buffer[128];
    ssize_t len = restore_stdout_and_read_buffer(buffer, sizeof(buffer));
    if (len == -1) {
        ck_abort_msg("Failed to restore stdout and read buffer");
    }

    ck_assert_msg(strcmp(buffer, expected_output) == 0,
			"Expected output was '%s', but actual output was '%s'",
			expected_output, buffer);
}

START_TEST(test_echo_1) {
	char* test_strings[] = {"echo", "Hello,", "World!", NULL};
	char* expected_output = "Hello, World!\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_2) {
	char* test_strings[] = {"echo", "-n", "Hello,", "World!", NULL};
	char* expected_output = "Hello, World!";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_3) {
	char* test_strings[] = {"echo", "-nn", "Hello,", "World!", NULL};
	char* expected_output = "Hello, World!";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_4) {
	char* test_strings[] = {"echo", "-nnnnnnnnn", "Hello,", "World!", NULL};
	char* expected_output = "Hello, World!";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_5) {
	char* test_strings[] = {"echo", "-s", "Hello,", "World!", NULL};
	char* expected_output = "-s Hello, World!\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_6)
{
	char* test_strings[] = {"echo", "-ns", "Hello,", "World!", NULL};
	char* expected_output = "-ns Hello, World!\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_7)
{
	char* test_strings[] = {"echo", NULL};
	char* expected_output = "\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_8)
{
	char* test_strings[] = {"echo", "-", NULL};
	char* expected_output = "\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_9)
{
	char* test_strings[] = {"echo", "-n", NULL};
	char* expected_output = "";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_10)
{
	char* test_strings[] = {"echo", "-n", "-n", "Hello,", "World!", NULL};
	char* expected_output = "Hello, World!";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_11)
{
	char* test_strings[] = {"echo", "-", "Hello,", "World!", NULL};
	char* expected_output = "Hello, World!\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

START_TEST(test_echo_12)
{
	char* test_strings[] = {"echo", "-n", "-s", "-n", "Hello,", "World!", NULL};
	char* expected_output = "-s -n Hello, World!";
	run_test_echo(test_strings, expected_output);
}
END_TEST

START_TEST(test_echo_13)
{
	char* test_strings[] = {"echo", "Hello,", "World!\n", NULL};
	char* expected_output = "Hello, World!\n\n";
	run_test_echo(test_strings, expected_output);
} END_TEST

Suite* echo_suite() {
    Suite* s = suite_create("echo");
    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_echo_1);
    tcase_add_test(tc_core, test_echo_2);
    tcase_add_test(tc_core, test_echo_3);
    tcase_add_test(tc_core, test_echo_4);
    tcase_add_test(tc_core, test_echo_5);
    tcase_add_test(tc_core, test_echo_6);
    tcase_add_test(tc_core, test_echo_7);
    tcase_add_test(tc_core, test_echo_8);
    tcase_add_test(tc_core, test_echo_9);
    tcase_add_test(tc_core, test_echo_10);
    tcase_add_test(tc_core, test_echo_11);
    tcase_add_test(tc_core, test_echo_12);
    suite_add_tcase(s, tc_core);
    return s;
}

#include "tests.h"

int main(void) {
    int number_failed;
    Suite *s1, *s2, *s3;
    SRunner *sr;

    s1 = echo_suite();
    s2 = env_suite();
	s3 = cd_suite();

    sr = srunner_create(s1);
    srunner_add_suite(sr, s2);
    srunner_add_suite(sr, s3);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

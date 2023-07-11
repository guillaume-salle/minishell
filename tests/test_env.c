#include "tests.h"

Suite* env_suite() {
    Suite* s = suite_create("env");
    TCase* tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_env_1);
	suite_add_tcase(s, tc_core);
    return s;
}

#include "tests.h"

t_vars g_vars;

int main(int argc, char *argv[], char *envp[]) {
	
	init_envp_list(envp, &(g_vars.envp_list));
   
   	int number_failed;
    Suite *s1, *s2, *s3, *s4, *s5, *s6, *s7;
    SRunner *sr;

    s1 = echo_suite();
    s2 = env_suite();
	s3 = cd_suite();
	s4 = pwd_suite();
	s5 = export_suite();
	s6 = unset_suite();
	s7 = exec_command_word_suite();

    sr = srunner_create(s1);
    srunner_add_suite(sr, s2);
    srunner_add_suite(sr, s3);
    srunner_add_suite(sr, s4);
    srunner_add_suite(sr, s5);
    srunner_add_suite(sr, s6);
    srunner_add_suite(sr, s7);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

#include "minishell.h"

// A simple function to create a t_commande for testing
 t_commande *create_command(char *cmd, int id) {
	t_commande *new_command = malloc(sizeof(t_commande));
	new_command->cmd = strdup(cmd);
	new_command->cmds_split = ft_split(cmd, ' ');
	new_command->id = id;
	new_command->next = NULL;
	return (new_command);
}

t_vars g_vars;

int main(int argc, char *argv[], char *envp[]) {

	init_envp_list(envp, &(g_vars.envp_list));

	t_commande *head = create_command("cat", WORD);
	head->next = create_command("< output1.txt", R_DIR);

	exec_command_list(head, &g_vars);

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/16 19:11:58 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int argc, char *argv[], char *envp[])
//{
//	t_vars	vars;
//
//	(void) argc;
//	(void) argv;
//	ft_memset(&vars, 0, sizeof(t_vars));
//	vars.envp_list = init_envp_list(envp);
//	if (!vars.envp_list)
//		return (-1);
//	return (0);
//}


//TESTING
void free_heredoc(t_heredoc *hd) {
    if (!hd) return;

    free(hd->filename);
    free(hd->file);
    free(hd);
}

void free_commande(t_commande *cmd) {
    if (!cmd) return;

    free(cmd->cmd);
    
    int i = 0;
    while (cmd->cmds_split[i]) {
        free(cmd->cmds_split[i]);
        i++;
    }
    free(cmd->cmds_split);
    
    free_heredoc(cmd->hd);
    
    t_commande *next;
    while (cmd) {
        next = cmd->next;
        free(cmd);
        cmd = next;
    }
}

void free_partition(t_partition *part) {
    if (!part) return;

    t_partition *next;
    while (part) {
        free_commande(part->cmds);
        next = part->next;
        free(part);
        part = next;
    }
}


int main() {
    // Initialize a heredoc (not used in this example, but shown for completeness)
    t_heredoc *hd = malloc(sizeof(t_heredoc));
    hd->filename = ft_strdup("some_file");
    hd->file = ft_strdup("This is the content of some_file.");

    // Initialize first command: cat example.txt
    t_commande *cmd1 = malloc(sizeof(t_commande));
    cmd1->cmd = ft_strdup("cat");
    cmd1->cmds_split = malloc(3 * sizeof(char*));
    cmd1->cmds_split[0] = ft_strdup("cat");
    cmd1->cmds_split[1] = ft_strdup("example.txt");
    cmd1->cmds_split[2] = NULL;
    cmd1->id = WORD;
    cmd1->hd = hd;
    cmd1->next = NULL;

    // Initialize second command: grep "hello"
    t_commande *cmd2 = malloc(sizeof(t_commande));
    cmd2->cmd = ft_strdup("grep");
    cmd2->cmds_split = malloc(3 * sizeof(char*));
    cmd2->cmds_split[0] = ft_strdup("grep");
    cmd2->cmds_split[1] = ft_strdup("hello");
    cmd2->cmds_split[2] = NULL;
    cmd2->id = WORD;
    cmd2->hd = NULL;  // Not using heredoc in this command
    cmd2->next = NULL;

    // Link commands
    cmd1->next = cmd2;

    // Initialize the partition
    t_partition *part = malloc(sizeof(t_partition));
    part->cmds = cmd1;
    part->pid = 1;  // Example PID
    part->next = NULL;

	// Execute partition
    exec_partition(part);

    // Cleaning up
    free_partition(part);

    return 0;
}
